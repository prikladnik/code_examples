program PrnClean;

uses
  Forms,
  Dialogs,
  SysUtils,
  UMain in 'UMain.pas' {FMain};

{$R *.res}

begin
  Application.Initialize;
  Application.Title:='PrnClean. Версия 1.1';
  Application.CreateForm(TFMain, FMain);
  if ParamCount<4 then
    begin
      ShowMessage(
        'PrnClean.exe p1 p2 p3 p4'+#13#10+
        '  p1 - путь к папке с файлами *.prn'+#13#10+
        '  p2 - путь к папке для размещения обработанных файлов'+#13#10+
        '  p3 - периодичность сканирования папки p1 (в сек)'+#13#10+
        '  p4 - полный путь к просмотровщику файлов *.frp'+#13#10+#13#10+
        'Например:'+#13#10+
        'PrnClean.exe "c:\Вход" "c:\Выход" 5 "c:\Program Files\FRViewer.exe"'
      );
      Application.Terminate;
    end
  else
    begin
      try
        FMain.InFolder:=ParamStr(1);
        FMain.OutFolder:=ParamStr(2);
        FMain.ReportViewerPath:=ParamStr(4);
        FMain.Timer1.Interval:=StrToInt(ParamStr(3))*1000;
        FMain.Timer1.Enabled:=true;
      except
        ShowMessage('Некорректные параметры запуска программы!');
      end;
    end;
  Application.ShowMainForm:=false;
  Application.Run;
  FMain.Hide;
end.
