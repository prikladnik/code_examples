unit UMessageService;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ComCtrls, Buttons, CheckLst;

type
PNetResourceArray = ^TNetResourceArray;
TNetResourceArray = array[0..MaxInt div SizeOf(TNetResource) - 1] of TNetResource;

  TfrmMessageService = class(TForm)
    Label1: TLabel;
    btnSentMessage: TSpeedButton;
    btnRefreshCompsList: TSpeedButton;
    mmoMsg: TMemo;
    Label2: TLabel;
    lstComps: TCheckListBox;
    mmoComps: TMemo;
    Label3: TLabel;
    SpeedButton1: TSpeedButton;
    procedure btnRefreshCompsListClick(Sender: TObject);
    procedure btnSentMessageClick(Sender: TObject);
    procedure SpeedButton1Click(Sender: TObject);
  private
    procedure RefreshCompsList;
  public
  end;

var
  frmMessageService: TfrmMessageService;

implementation

uses Math, UMessageSendThread;

{$R *.dfm}

procedure TfrmMessageService.btnRefreshCompsListClick(Sender: TObject);
begin
  RefreshCompsList;
end;

procedure TfrmMessageService.btnSentMessageClick(Sender: TObject);
var
  i, j :integer;
  s :string;
  MsgRecipients :TMsgRecipients;
begin
  j:=0;
  // подсчитываем количество выбранных компьютеров
  for i:=0 to lstComps.Count-1 do
    if lstComps.Checked[i] then Inc(j);
  if j=0 then
    ShowMessage('Не выбрано ни одного компьютера для отправки сообщения!')
  else
    begin
      SetLength(MsgRecipients, j);
      // заполняем массив получателей сообщения
      j:=-1;
      for i:=0 to lstComps.Count-1 do
        begin
          if lstComps.Checked[i] then
            begin
              Inc(j);
              MsgRecipients[j].CompName:=lstComps.Items.Strings[i];
            end;
        end;
      SendNetMessage(MsgRecipients,mmoMsg.Text);
      // выводим результаты
      s:='';
      for i:=0 to High(MsgRecipients) do
        begin
          s:=s+MsgRecipients[i].CompName;
          if MsgRecipients[i].Status=0 then
            s:=s+' доставлено'+#13#10
          else
            s:=s+' проблемы'+#13#10;
        end;
       ShowMessage(s);
    end;
end;

function GetComputerNetName: string;
var
  buffer: array[0..255] of char;
  size: dword;
begin
  size:=256;
  if GetComputerName(buffer, size) then
    Result:=buffer
  else
    Result:='';
end;

procedure TfrmMessageService.RefreshCompsList;
var
  cur: TCursor;
  NetHandle: DWORD;
  BufSize: DWORD;
  NetResources: PNetResourceArray;
  n: DWORD;
  i :integer;
  s :string;
begin
  cur:=Screen.Cursor;
  Screen.Cursor:=crHourGlass;
  lstComps.Items.Clear;
  NetResources:=nil;
  if
    WNetOpenEnum(RESOURCE_CONTEXT, RESOURCETYPE_ANY,0,nil,NetHandle)<>NO_ERROR
  then
    Exit;

  try
    BufSize:=50 * SizeOf(TNetResource);
    GetMem(NetResources, BufSize);
    n:=1;
    while WNetEnumResource(NetHandle, n, NetResources, BufSize)=NO_ERROR do
      begin
        for i:=0 to n-1 do
          if NetResources^[i].LpRemoteName<>nil then
            begin
              s:=NetResources^[i].LpRemoteName;
              if s[1]='\' then
                lstComps.Items.Add(Copy(s,3,Length(s)-2))
              else
                lstComps.Items.Add(s);
            end;
      end;
    Screen.Cursor:=cur;
  finally
    if NetResources<>nil then FreeMem(NetResources,BufSize);
  end;
end;

procedure TfrmMessageService.SpeedButton1Click(Sender: TObject);
var
  i :integer;
  s :string;
  MsgRecipients :TMsgRecipients;
begin
  SetLength(MsgRecipients, mmoComps.Lines.Count);
  // заполняем массив получателей сообщения
  for i:=0 to mmoComps.Lines.Count-1 do
    MsgRecipients[i].CompName:=mmoComps.Lines.Strings[i];
  SendNetMessage(MsgRecipients,mmoMsg.Text);
  // выводим результаты
  s:='';
  for i:=0 to High(MsgRecipients) do
    begin
      s:=s+MsgRecipients[i].CompName;
      if MsgRecipients[i].Status=0 then
        s:=s+' доставлено'+#13#10
      else
        s:=s+' проблемы'+#13#10;
    end;
  MsgRecipients:=nil;
  ShowMessage(s);
end;

end.

