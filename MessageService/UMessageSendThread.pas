unit UMessageSendThread;

interface

uses Classes, Types, Dialogs, Windows, SysUtils;

type
  TMsgRecipient=record
    // имя компьютера-получателя
    CompName :string;
    // статус отправки сообщения (0 - успешно доставлено)
    Status :integer;
  end;

  TMsgRecipients=array of TMsgRecipient;

  PNetMessageBufferSend = ^TNetMessageBufferSend;
  TNetMessageBufferSend = function(
    servername: PWideChar;
    msgname: PWideChar;
    fromname: PWideChar;
    buf: PBYTE;
    buflen: DWORD
  ): Integer; stdcall;

  TNetMessageThread = class(TThread)
  private
    // компьютер адресат
    wTo :PWideChar;
    // текст сообщения
    wMessage :PWideChar;
    MessageLength :integer;
    NetMessageBufferSend :TNetMessageBufferSend;
    pThreadIndex :integer;
    function SendNetMessage :integer;    
  protected
    procedure Execute; override;
  public
    constructor Create(sMessage, sTo :string;
      NetMessageBufferSend :TNetMessageBufferSend; pThreadIndex :integer);
  end;
  {
    Отправляет сообщение с текстом pMsg каждому компьютеру-адресату из MsgRecipients.
    Максимальное количество получателей в массиве MsgRecipients равно системной
    константе MAXIMUM_WAIT_OBJECTS (около 64).
    Для каждого i-го получателя в поле MsgRecipients[i].Status фиксируется статус
    доставки сообщения (равен результату, возвращаемому функцией NetMessageBufferSend).
    Status = 0, если сообщение было успешно доставлено.
  }
  function SendNetMessage(var MsgRecipients :TMsgRecipients; pMsg :string) :integer;

implementation

var
  ThreadStatus :array of integer;

{ TNetMessageThread }

constructor TNetMessageThread.Create(sMessage, sTo :string;
  NetMessageBufferSend :TNetMessageBufferSend; pThreadIndex :integer);
begin
  // выделяем память для сообщения
  GetMem(Self.wMessage,(Length(sMessage)+1)*sizeof(WideChar));
  StringToWideChar(sMessage,Self.wMessage,Length(sMessage)+1);
  // выделяем память для имени компьютера
  GetMem(Self.wTo,(Length(sTo)+1)*sizeof(WideChar));
  StringToWideChar(sTo,Self.wTo,Length(sTo)+1);
  // сохраняем длину сообщения
  MessageLength:=Length(sMessage);
  Self.NetMessageBufferSend:=NetMessageBufferSend;
  Self.pThreadIndex:=pThreadIndex;
  FreeOnTerminate:=true;
  inherited Create(false);
end;

procedure TNetMessageThread.Execute;
begin
  ThreadStatus[pThreadIndex]:=SendNetMessage;
  // удаляем сообщение и название компа из памяти
  FreeMem(wTo, (Length(wTo)+1)*sizeof(WideChar));
  FreeMem(wMessage, (Length(wMessage)+1)*sizeof(WideChar));
end;

function TNetMessageThread.SendNetMessage: integer;
begin
  try
    Result:=NetMessageBufferSend(nil, wTo, nil, PBYTE(wMessage),
      (MessageLength + 1)*sizeof(WideChar));
  except
    Result:=-1;
  end;
end;

function SendNetMessage(var MsgRecipients :TMsgRecipients; pMsg :string) :integer;
var
  i, hLib :Integer;
  NetMessageBufferSend :TNetMessageBufferSend;
  // массив хэндлов потоков. если использовать динамический массив,
  // функция WaitForMultipleObjects не срабатывает                                 
  Threads :array[0..MAXIMUM_WAIT_OBJECTS-1] of THandle;
  NetMessageThread :TNetMessageThread;
begin
  Result:=-1;
  // по умолчанию ни одно сообщение не доставлено
  for i:=0 to High(MsgRecipients) do
    MsgRecipients[i].Status:=-1;
  // должны быть получатели, и их количество не больше допустимого
  if
    (High(MsgRecipients)>=0) and
    (High(MsgRecipients)+1<=MAXIMUM_WAIT_OBJECTS)
  then
    begin
      hLib:=LoadLibrary('NetApi32.dll');
      if hlib>0 then
        try
          @NetMessageBufferSend:=GetProcAddress(hLib,'NetMessageBufferSend');
          if @NetMessageBufferSend<>nil then
            begin
              SetLength(ThreadStatus,High(MsgRecipients)+1);
              for i:=0 to High(ThreadStatus) do
                ThreadStatus[i]:=-1;
              for i:=0 to High(MsgRecipients) do
                begin
                  try
                    NetMessageThread:=TNetMessageThread.Create(
                      pMsg,MsgRecipients[i].CompName,@NetMessageBufferSend,i
                    );
                    Threads[i]:=NetMessageThread.Handle;
                  finally
                  end;
                end;
              // ждем, пока все потоки завершатся
              WaitForMultipleObjects(High(MsgRecipients)+1,@Threads,true,INFINITE);
              Result:=0;
            end
          else
            ShowMessage('Функция NetMessageBufferSend не обнаружена');
        finally
          // сохраняем результаты отправки сообщений
          for i:=0 to High(MsgRecipients) do
            MsgRecipients[i].Status:=ThreadStatus[i];
          ThreadStatus:=nil;
          FreeLibrary(hLib);
        end
      else
        ShowMessage('NetApi32.dll не загружена');
    end;
end;

end.
