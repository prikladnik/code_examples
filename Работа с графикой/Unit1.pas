unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, ActnList;

const
  Beg_X = 336;
  Beg_Y = 301;
  Beg_Angle = 0;
  PointsCount = 12;

type
  TPoint = record
    x, y :real; // координаты точки
    k :real; // коэффециент масштабирования
  end;

type
  TForm1 = class(TForm)
    PaintBox: TPaintBox;
    ActionList1: TActionList;
    actLeft: TAction;
    actRight: TAction;
    actZoomIn: TAction;
    actUp: TAction;
    actDown: TAction;
    actReturn: TAction;
    actZoomOut: TAction;
    actRotateLeft: TAction;
    actRotateRight: TAction;
    actFlipOX: TAction;
    actFlipOY: TAction;
    actFlipXY: TAction;
    Panel1: TPanel;
    btnUp: TButton;
    btnLeft: TButton;
    btnRight: TButton;
    btnDown: TButton;
    btnReturn: TButton;
    Button1: TButton;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    Button6: TButton;
    Button7: TButton;
    Label1: TLabel;
    actFreeRotate: TAction;
    Label2: TLabel;
    procedure FormShow(Sender: TObject);
    procedure PaintBoxPaint(Sender: TObject);
    procedure actLeftExecute(Sender: TObject);
    procedure actRightExecute(Sender: TObject);
    procedure actZoomInExecute(Sender: TObject);
    procedure actReturnExecute(Sender: TObject);
    procedure actUpExecute(Sender: TObject);
    procedure actDownExecute(Sender: TObject);
    procedure actRotateLeftExecute(Sender: TObject);
    procedure actRotateRightExecute(Sender: TObject);
    procedure actFlipOXExecute(Sender: TObject);
    procedure actFlipOYExecute(Sender: TObject);
    procedure actFlipXYExecute(Sender: TObject);
    procedure PaintBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
      Y: Integer);
    procedure actZoomOutExecute(Sender: TObject);
    procedure PaintBoxMouseDown(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
  private
    FCurX: integer;
    FCurY: integer;
    FCurAngle: real;
    Mas :array[1..PointsCount] of TPoint; // массив точек фигуры
    Dop :array [1..3] of array [1..3] of real;			//матрица преобразования
    procedure SetCurX(const Value: integer);
    procedure SetCurY(const Value: integer);
    procedure SetCurAngle(const Value: real);
  private
    // текущее положение фигуры на рисунке
    property CurX :integer read FCurX write SetCurX;
    property CurY :integer read FCurY write SetCurY;
    property CurAngle :real read FCurAngle write SetCurAngle; // в радианах
    procedure Clear;
    procedure Init;
  public
    procedure DrawFigure;
    // отрисовка осей координат
    procedure DrawXY;
    procedure DrawAll;
  end;

var
  Form1: TForm1;

implementation

uses Math;

{$R *.dfm}

procedure TForm1.DrawFigure;
var
  i, j :integer;
  Buf :array [1..3] of real;
begin
  Dop[1][1]:=Cos(CurAngle);         					//если угол поворота не равен 0 то матрица
  Dop[2][1]:=Sin(CurAngle);						//преобразования изменится
  Dop[1][2]:=-Sin(CurAngle);
  Dop[2][2]:=Dop[1][1];
   for i:=1 to PointsCount do         					//умножаем матрицу вершин на матрицу
     begin							//преобразования и получаем обновленную
       for j:=1 to 3 do						//матрицу вершин
         begin
           Buf[j]:=Dop[j][1]*Mas[i].x+Dop[j][2]*Mas[i].y+Dop[j][3]*Mas[i].k;
         end;
       Mas[i].x := Buf[1]/Buf[3];			//третья координата вершин должна быть
       Mas[i].y := Buf[2]/Buf[3];			//равна 1, поэтому делим на нее все координаты
       Mas[i].k := 1;
     end;      
  // рисуем квадрат
  PaintBox.Canvas.MoveTo(CurX + Round(Mas[1].x), CurY + Round(Mas[1].y));
  for i := 2 to 5 do
    PaintBox.Canvas.LineTo(CurX + Round(Mas[i].x), CurY + Round(Mas[i].y));
  // рисуем вложенную фигуру
  PaintBox.Canvas.MoveTo(CurX + Round(Mas[5].x), CurY + Round(Mas[5].y));
  for i := 6 to PointsCount do
    PaintBox.Canvas.LineTo(CurX + Round(Mas[i].x), CurY + Round(Mas[i].y));
end;

procedure TForm1.FormShow(Sender: TObject);
begin
  Init;
end;

procedure TForm1.DrawXY;
begin
  PaintBox.Canvas.Pen.Width := 3;
  PaintBox.Canvas.MoveTo(PaintBox.Width div 2, 0);
  PaintBox.Canvas.LineTo(PaintBox.Width div 2, PaintBox.Height);
  PaintBox.Canvas.MoveTo(0, PaintBox.Height div 2);
  PaintBox.Canvas.LineTo(PaintBox.Width, PaintBox.Height div 2);
end;

procedure TForm1.SetCurX(const Value: integer);
begin
  FCurAngle := 0;
  Dop[3][3] := 1;
  FCurX := Value;
  Clear;
  DrawAll;
end;

procedure TForm1.SetCurY(const Value: integer);
begin
  FCurAngle := 0;
  Dop[3][3] := 1;
  FCurY := Value;
  Clear;
  DrawAll;
end;

procedure TForm1.Clear;
begin
  PaintBox.Canvas.Brush.Color := clWhite;
  PaintBox.Canvas.FillRect(PaintBox.Canvas.ClipRect);
end;

procedure TForm1.DrawAll;
begin
  DrawXY;
  DrawFigure;
end;

procedure TForm1.PaintBoxPaint(Sender: TObject);
begin
  Clear;
  DrawAll;
end;

procedure TForm1.actLeftExecute(Sender: TObject);
begin
  CurX := CurX - 2;
end;

procedure TForm1.actRightExecute(Sender: TObject);
begin
  CurX := CurX + 2;
end;

procedure TForm1.SetCurAngle(const Value: real);
begin
  FCurAngle := Value;
  Clear;
  DrawAll;  
end;

procedure TForm1.actReturnExecute(Sender: TObject);
begin
  FCurX := Beg_X;
  FCurY := Beg_Y;
  FCurAngle := Beg_Angle;
  Init;
  Clear;
  DrawAll;
end;

procedure TForm1.actUpExecute(Sender: TObject);
begin
  CurY := CurY - 2;
end;

procedure TForm1.actDownExecute(Sender: TObject);
begin
  CurY := CurY + 2;
end;

procedure TForm1.actRotateLeftExecute(Sender: TObject);
begin
  if CurAngle < 0 then
    FCurAngle := 0;
  Dop[3][3] := 1;
  CurAngle := CurAngle + 0.001;
end;

procedure TForm1.actRotateRightExecute(Sender: TObject);
begin
  if CurAngle > 0 then
    FCurAngle := 0;
  Dop[3][3] := 1;
  CurAngle := CurAngle - 0.001;
end;

procedure TForm1.actFlipOXExecute(Sender: TObject);
var
 i : integer;
begin
  for i := 1 to PointsCount do
    Mas[i].y := -Mas[i].y;
  Clear;
  DrawAll;
end;

procedure TForm1.actFlipOYExecute(Sender: TObject);
var
 i : integer;
begin
  for i := 1 to PointsCount do
    Mas[i].x := -Mas[i].x;
  Clear;
  DrawAll;
end;

procedure TForm1.actFlipXYExecute(Sender: TObject);
var
 i    : integer;
 buf  : real;
begin
  for i := 1 to PointsCount do						//меняем координаты х и у местами
    begin							//приходится учитывать, что в мониторе 
      buf := -Mas[i].x;						//у-координата увеличивается в направлении
      Mas[i].x := -Mas[i].y;					//сверху вниз, а нам надо наооборот
      Mas[i].y := buf;
    end;
  Clear;
  DrawAll;
end;

procedure TForm1.PaintBoxMouseMove(Sender: TObject; Shift: TShiftState; X,
  Y: Integer);
begin
  Label1.Caption := IntToStr(x) + ' ' + IntToStr(y);
end;

procedure TForm1.Init;
var
  i :integer;
begin
  FCurX := Beg_X;
  FCurY := Beg_Y;
  FCurAngle := Beg_Angle;
  // координаты точек квадрата
  Mas[1].x := 50; Mas[1].y := 50;
  Mas[2].x := 250; Mas[2].y := 50;
  Mas[3].x := 250; Mas[3].y := 225;
  Mas[4].x := 50; Mas[4].y := 225;
  Mas[5].x := 50; Mas[5].y := 50;
  // координаты вложенной фигуры
  Mas[6].x := 150; Mas[6].y := 50;
  Mas[7].x := 175; Mas[7].y := 150;
  Mas[8].x := 250; Mas[8].y := 225;
  Mas[9].x := 150; Mas[9].y := 200;
  Mas[10].x := 50; Mas[10].y := 225;
  Mas[11].x := 125; Mas[11].y := 150;
  Mas[12].x := 150; Mas[12].y := 50;
  // устанавливаем масштабный коэффециент
  for i:=1 to PointsCount do
    Mas[i].k := 1;
  Dop[1][1]:=1;   Dop[2][1]:=0;   Dop[3][1]:=0;			//задаем матрицу преобразования
  Dop[1][2]:=0;   Dop[2][2]:=1;   Dop[3][2]:=0;			//единичной матрицей
  Dop[1][3]:=0;   Dop[2][3]:=0;   Dop[3][3]:=1;
end;

procedure TForm1.actZoomInExecute(Sender: TObject);
begin
  FCurAngle := 0;
  if Dop[3][3] > 1 then
    Dop[3][3] := 1;
  Dop[3][3] := Dop[3][3] - 0.001;
  Clear;
  DrawAll;
end;

procedure TForm1.actZoomOutExecute(Sender: TObject);
begin
  FCurAngle := 0;
  if Dop[3][3] < 1 then
    Dop[3][3] := 1;
  Dop[3][3] := Dop[3][3] + 0.001;
  Clear;
  DrawAll;
end;

procedure TForm1.PaintBoxMouseDown(Sender: TObject; Button: TMouseButton;
  Shift: TShiftState; X, Y: Integer);
begin
  if
    (Button = mbLeft) and
    (MessageDlg('Переместить центр координат в эту точку?',
      mtConfirmation, [mbYes, mbNo],0) = mrYes)
  then begin
    CurX := X;							//перемещаем центр координат в точку, куда
    CurY := Y;							//кликнули
    Clear;
    DrawAll;
  end;
end;

end.
