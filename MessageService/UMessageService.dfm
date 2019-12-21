object frmMessageService: TfrmMessageService
  Left = 430
  Top = 291
  BorderStyle = bsDialog
  Caption = #1055#1086#1076#1089#1080#1089#1090#1077#1084#1072' '#1086#1090#1087#1088#1072#1074#1082#1080' '#1089#1086#1086#1073#1097#1077#1085#1080#1081
  ClientHeight = 376
  ClientWidth = 441
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 144
    Width = 116
    Height = 13
    Caption = #1042#1099#1073#1077#1088#1080#1090#1077' '#1087#1086#1083#1091#1095#1072#1090#1077#1083#1077#1081
  end
  object btnSentMessage: TSpeedButton
    Left = 117
    Top = 344
    Width = 100
    Height = 25
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
    OnClick = btnSentMessageClick
  end
  object btnRefreshCompsList: TSpeedButton
    Left = 8
    Top = 344
    Width = 100
    Height = 25
    Caption = #1054#1073#1085#1086#1074#1080#1090#1100
    OnClick = btnRefreshCompsListClick
  end
  object Label2: TLabel
    Left = 8
    Top = 8
    Width = 58
    Height = 13
    Caption = #1057#1086#1086#1073#1097#1077#1085#1080#1077
  end
  object Label3: TLabel
    Left = 232
    Top = 144
    Width = 108
    Height = 13
    Caption = #1048#1083#1080' '#1074#1074#1077#1076#1080#1090#1077' '#1074#1088#1091#1095#1085#1091#1102
  end
  object SpeedButton1: TSpeedButton
    Left = 333
    Top = 343
    Width = 100
    Height = 25
    Caption = #1054#1090#1087#1088#1072#1074#1080#1090#1100
    OnClick = SpeedButton1Click
  end
  object mmoMsg: TMemo
    Left = 8
    Top = 24
    Width = 425
    Height = 113
    Lines.Strings = (
      #1055#1088#1086#1089#1090#1086' '#1089#1086#1086#1073#1097#1077#1085#1080#1077'.'
      'It'#39's simple message.')
    TabOrder = 0
  end
  object lstComps: TCheckListBox
    Left = 8
    Top = 160
    Width = 209
    Height = 177
    ItemHeight = 13
    TabOrder = 1
  end
  object mmoComps: TMemo
    Left = 232
    Top = 160
    Width = 201
    Height = 177
    Lines.Strings = (
      'oks03'
      'oks16'
      'oks17')
    TabOrder = 2
  end
end
