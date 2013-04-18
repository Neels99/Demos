unit dialogbar;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms, jpeg, pngimage,
  Dialogs, StdCtrls, ExtCtrls;

type
  Tdlgform = class(TForm)
    Button1: TButton;
    Image1: TImage;
    Label1: TLabel;
    Label2: TLabel;
    Label3: TLabel;
    procedure FormCreate(Sender: TObject);
    procedure Button1KeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
  private
    { Private declarations }
    procedure LoadImg(source:string);
  public
    { Public declarations }
    procedure SetParams(title,brief,maincontext,secondarycontext,imgpath:string);
  end;

var
  dlgform: Tdlgform;

implementation

{$R *.dfm}

{ TForm2 }

procedure Tdlgform.Button1KeyDown(Sender: TObject; var Key: Word; Shift: TShiftState);
begin
  if key = VK_ESCAPE then ModalResult := mrOk;
end;

procedure Tdlgform.FormCreate(Sender: TObject);
begin
  Image1.Picture := nil;

  Label1.Caption := '';
  Label2.Caption := '';
  Label3.Caption := '';

  Caption := Application.Title;
end;

procedure Tdlgform.LoadImg(source: string);
var fext : string;
    img: TGraphic;
begin
  try
    if not fileexists(source) then raise Exception.Create('wrong path'); 
    Image1.Picture := nil;
    fext := ExtractFileExt(source);
    if fext = '.bmp' then Image1.Picture.LoadFromFile(source) else
    begin
      if (fext = '.jpg') or (fext = '.jpeg') then img := TJPEGImage.Create;
      if (fext = '.png') then img := TPngImage.Create;
      img.LoadFromFile(source);
      Image1.Picture.Bitmap.Assign(img);
      img.Free;
    end;
    if Image1.Picture = nil then raise Exception.Create('Format error');
  except on e:exception do
    begin
      Image1.Canvas.Rectangle(0,0,Image1.Width,Image1.Height);
      Image1.Canvas.TextOut(5,2,e.Message);
    end;
  end;
end;

procedure Tdlgform.SetParams(title, brief, maincontext, secondarycontext, imgpath: string);
begin
  if(title <> '') then Caption := title;

  Label1.Caption := brief;
  Label2.Caption := maincontext;
  Label3.Caption := secondarycontext;

  LoadImg(imgpath);
end;

end.
