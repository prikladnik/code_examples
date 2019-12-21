unit UMain;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, ExtCtrls, ShellApi;

type
  TFMain = class(TForm)
    Timer1: TTimer;
    procedure Timer1Timer(Sender: TObject);
  private
    FOutFolder: string;
    FInFolder: string;
    FViewerPath: string;
    procedure SetInFolder(const Value: string);
    procedure SetOutFolder(const Value: string);
    procedure SetViewerPath(const Value: string);
  public
    procedure ScanAndClean;
    function PrepareFolderPath(pFolder :string) :string;
  published
    // папка с исходными файлами
    property InFolder :string read FInFolder write SetInFolder;
    // папка с файлами результатов
    property OutFolder :string read FOutFolder write SetOutFolder;
    // путь запуска FRViewer.exe
    property ReportViewerPath :string read FViewerPath write SetViewerPath;
  end;

var
  FMain: TFMain;

implementation

{$R *.dfm}

{ TFMain }

function TFMain.PrepareFolderPath(pFolder: string): string;
begin
  if (pFolder[length(pFolder)]<>'\') then Result:=pFolder;
end;

procedure TFMain.ScanAndClean;
var
  inFile, outFile :TextFile;
  i :integer;
  sr: TSearchRec;
  s, s_part, line, parFr :string;
begin
  try
    if FindFirst(InFolder+'\*.*', faAnyFile, sr) = 0 then
      begin
        repeat
          if (AnsiLowerCase(ExtractFileExt(sr.Name))='.prn') then
            begin
              AssignFile(inFile,InFolder+'\'+sr.Name);
              Reset(inFile);
              s:='';
              i:=0;
              s_part:='';
              while not EOF(inFile) do
                begin
                  Readln(inFile, line);
                  if (Trim(line)<>'') then
                    begin
                      if i=0 then
                        s:=s+line+#13#10
                      else
                        begin
                          if (i>3) and (s<>'') then s:=s+#12+line+#13#10
                            else s:=s+line+#13#10;
                          i:=0;
                          s_part:='';
                        end
                    end
                  else
                    begin
                      s_part:=s_part+line+#13#10;
                      Inc(i);
                    end;
                end;
              CloseFile(InFile);
              AssignFile(outFile,OutFolder+'\'+sr.Name);
              Rewrite(outFile);
              Write(OutFile,s);
              CloseFile(OutFile);
              DeleteFile(InFolder+'\'+sr.Name);
            end
          else if (AnsiLowerCase(ExtractFileExt(sr.Name))='.frp') then
            begin
              AssignFile(outFile,OutFolder+'\'+sr.Name);
              if CopyFile(
                PChar(InFolder+'\'+sr.Name),PChar(OutFolder+'\'+sr.Name),true
              ) then
                begin
                  DeleteFile(InFolder+'\'+sr.Name);
                  if Pos('[1]',sr.Name)>0 then
                    ParFr:='\p' // печать отчета сразу после открытия, без просмотра
                  else
                    ParFr:='';
                  ShellExecute(
                    Application.Handle,'Open',
                    PChar('"'+ReportViewerPath+'"'),
                    PChar('"'+OutFolder+'\'+sr.Name+'" '+ParFr),
                    nil,SW_SHOWNORMAL
                  );
                end;
            end;
        until FindNext(sr) <> 0;
        FindClose(sr);
      end;
  except
    ShowMessage('Ошибка при обработке файлов!');
  end;
end;

procedure TFMain.SetInFolder(const Value: string);
begin
  FInFolder:=PrepareFolderPath(Value);
end;

procedure TFMain.SetOutFolder(const Value: string);
begin
  FOutFolder:=PrepareFolderPath(Value);
end;

procedure TFMain.SetViewerPath(const Value: string);
begin
  FViewerPath:=Value;
end;

procedure TFMain.Timer1Timer(Sender: TObject);
begin
  Timer1.Enabled:=false;
  ScanAndClean;
  Timer1.Enabled:=true;
end;

end.
