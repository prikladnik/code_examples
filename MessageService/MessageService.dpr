program MessageService;

uses
  Forms,
  UMessageService in 'UMessageService.pas' {frmMessageService},
  UMessageSendThread in 'UMessageSendThread.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TfrmMessageService, frmMessageService);
  Application.Run;
end.
