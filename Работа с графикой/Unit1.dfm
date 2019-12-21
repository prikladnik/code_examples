object Form1: TForm1
  Left = 426
  Top = 202
  Width = 921
  Height = 681
  Caption = #1043#1088#1072#1092#1080#1082#1072
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox: TPaintBox
    Left = 0
    Top = 0
    Width = 584
    Height = 643
    Align = alClient
    Color = clWhite
    ParentColor = False
    OnMouseDown = PaintBoxMouseDown
    OnMouseMove = PaintBoxMouseMove
    OnPaint = PaintBoxPaint
  end
  object Panel1: TPanel
    Left = 584
    Top = 0
    Width = 321
    Height = 643
    Align = alRight
    TabOrder = 0
    object Label1: TLabel
      Left = 20
      Top = 351
      Width = 32
      Height = 13
      Caption = 'Label1'
    end
    object Label2: TLabel
      Left = 13
      Top = 390
      Width = 182
      Height = 39
      Caption = 
        #1053#1072#1078#1084#1080#1090#1077' '#1083#1077#1074#1086#1081' '#1082#1085#1086#1087#1082#1086#1081' '#1084#1099#1096#1082#1080' '#1085#1072' '#1088#1080#1089#1091#1085#1082#1077', '#1095#1090#1086#1073#1099' '#1080#1079#1084#1077#1085#1080#1090#1100' '#1094#1077#1085#1090#1088' '#1082#1086#1086 +
        #1088#1076#1080#1085#1072#1090
      WordWrap = True
    end
    object btnUp: TButton
      Left = 95
      Top = 25
      Width = 75
      Height = 25
      Action = actUp
      TabOrder = 0
    end
    object btnLeft: TButton
      Left = 15
      Top = 66
      Width = 75
      Height = 24
      Action = actLeft
      TabOrder = 1
    end
    object btnRight: TButton
      Left = 175
      Top = 66
      Width = 75
      Height = 24
      Action = actRight
      TabOrder = 2
    end
    object btnDown: TButton
      Left = 95
      Top = 106
      Width = 75
      Height = 25
      Action = actDown
      TabOrder = 3
    end
    object btnReturn: TButton
      Left = 103
      Top = 58
      Width = 57
      Height = 40
      Action = actReturn
      TabOrder = 4
    end
    object Button1: TButton
      Left = 132
      Top = 162
      Width = 116
      Height = 21
      Action = actZoomIn
      TabOrder = 5
    end
    object Button2: TButton
      Left = 8
      Top = 163
      Width = 116
      Height = 21
      Action = actZoomOut
      TabOrder = 6
    end
    object Button3: TButton
      Left = 7
      Top = 189
      Width = 117
      Height = 20
      Action = actRotateLeft
      TabOrder = 7
    end
    object Button4: TButton
      Left = 130
      Top = 189
      Width = 118
      Height = 20
      Action = actRotateRight
      TabOrder = 8
    end
    object Button5: TButton
      Left = 7
      Top = 241
      Width = 117
      Height = 20
      Action = actFlipOX
      TabOrder = 9
    end
    object Button6: TButton
      Left = 7
      Top = 267
      Width = 117
      Height = 20
      Action = actFlipOY
      TabOrder = 10
    end
    object Button7: TButton
      Left = 7
      Top = 293
      Width = 117
      Height = 20
      Action = actFlipXY
      TabOrder = 11
    end
  end
  object ActionList1: TActionList
    Left = 640
    Top = 144
    object actLeft: TAction
      Caption = #1042#1083#1077#1074#1086
      ShortCut = 16460
      OnExecute = actLeftExecute
    end
    object actRight: TAction
      Caption = #1042#1087#1088#1072#1074#1086
      ShortCut = 16466
      OnExecute = actRightExecute
    end
    object actZoomIn: TAction
      Caption = #1059#1074#1077#1083#1080#1095#1080#1090#1100
      OnExecute = actZoomInExecute
    end
    object actUp: TAction
      Caption = #1042#1074#1077#1088#1093
      OnExecute = actUpExecute
    end
    object actDown: TAction
      Caption = #1042#1085#1080#1079
      OnExecute = actDownExecute
    end
    object actReturn: TAction
      Caption = #1042#1086#1079#1074#1088#1072#1090
      OnExecute = actReturnExecute
    end
    object actZoomOut: TAction
      Caption = #1059#1084#1077#1085#1100#1096#1080#1090#1100
      OnExecute = actZoomOutExecute
    end
    object actRotateLeft: TAction
      Caption = #1055#1086#1074#1077#1088#1085#1091#1090#1100' '#1085#1072#1083#1077#1074#1086
      OnExecute = actRotateLeftExecute
    end
    object actRotateRight: TAction
      Caption = #1055#1086#1074#1077#1088#1085#1091#1090#1100' '#1085#1072#1087#1088#1072#1074#1086
      OnExecute = actRotateRightExecute
    end
    object actFlipOX: TAction
      Caption = #1054#1090#1088#1072#1079#1080#1090#1100' '#1087#1086' '#1054#1061
      OnExecute = actFlipOXExecute
    end
    object actFlipOY: TAction
      Caption = #1054#1090#1088#1072#1079#1080#1090#1100' '#1087#1086' OY'
      OnExecute = actFlipOYExecute
    end
    object actFlipXY: TAction
      Caption = #1054#1090#1088#1072#1079#1080#1090#1100' '#1087#1086' XY'
      OnExecute = actFlipXYExecute
    end
    object actFreeRotate: TAction
      Caption = #1055#1088#1086#1080#1079#1074#1086#1083#1100#1085#1086#1077' '#1074#1088#1072#1097#1077#1085#1080#1077
    end
  end
end
