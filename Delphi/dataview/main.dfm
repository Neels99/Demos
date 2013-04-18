object Form1: TForm1
  Left = 0
  Top = 0
  ActiveControl = ListBox1
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Data view'
  ClientHeight = 309
  ClientWidth = 495
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object ListBox1: TListBox
    AlignWithMargins = True
    Left = 3
    Top = 3
    Width = 489
    Height = 256
    Style = lbOwnerDrawFixed
    Align = alClient
    TabOrder = 0
    OnClick = ListBox1Click
    OnDrawItem = ListBox1DrawItem
    OnKeyDown = ListBox1KeyDown
    OnMouseDown = ListBox1MouseDown
    ExplicitHeight = 303
  end
  object Panel1: TPanel
    AlignWithMargins = True
    Left = 3
    Top = 265
    Width = 489
    Height = 41
    Align = alBottom
    BevelOuter = bvNone
    TabOrder = 1
    object Button1: TButton
      Left = 408
      Top = 9
      Width = 75
      Height = 25
      Caption = 'More'
      TabOrder = 0
      OnClick = Button1Click
    end
  end
  object MainMenu1: TMainMenu
    Left = 432
    Top = 88
    object Menu1: TMenuItem
      Caption = 'Menu'
      object Load1: TMenuItem
        Caption = 'Load XML'
        ShortCut = 113
        OnClick = Load1Click
      end
      object Clear1: TMenuItem
        Caption = 'Clear'
        ShortCut = 114
        OnClick = Clear1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Exit1: TMenuItem
        Caption = 'Exit'
        OnClick = Exit1Click
      end
    end
  end
  object xd: TXMLDocument
    FileName = '../test.xml'
    Left = 432
    Top = 24
    DOMVendorDesc = 'MSXML'
  end
  object Timer1: TTimer
    Interval = 10
    OnTimer = Timer1Timer
    Left = 432
    Top = 144
  end
end
