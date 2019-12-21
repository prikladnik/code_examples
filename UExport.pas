unit UExport;

interface

uses
  Variants, DB, SysUtils, ExcelXP, DBGrids;

type
  DynArrInt = array of integer;
  TFreeParams=array of array of string;

{
  Установление формата для "не float" столбцов листа vXLSheet
  pDBGrid - таблица, столбцы из которой будут потом выводиться на лист
    (пока используется только формат ее столбцов)
  vOutCols - массив с номерами выводимых столбцов
  Col, Row - номера столбца и строки ячейки, с которой будет начинаться
    вывод
}
procedure SetColumnFormat(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet :variant; Col, Row :integer);
{
  Установление формата для столбцов типа float листа vXLSheet
  pDBGrid - таблица, столбцы из которой будут потом выводиться на лист
    (пока используется только формат ее столбцов)
  vOutCols - массив с номерами выводимых столбцов
  Col, Row - номера столбца и строки ячейки, с которой будет начинаться
    вывод
}
procedure SetColumnFloatFormat(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet :variant; Col, Row :integer; vArrayData: Variant);
{
  Заполнение листа vXLSheet строками из pDBGrid
  vOutCols - массив с номерами выводимых столбцов
  Col, Row - номера столбца и строки ячейки, с которой нужно начинать вывод
}
procedure OutGrid(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet: variant; Col, Row: integer);
// Version - строка, возвращаемая Application.Version
function IsOffice2007(Version :string) :boolean;
function GetExcelExt(Version :string) :string;
function GetWordExt(Version :string) :string;

const
  // максимальное количество разбора столбцов типа float по-ячейкам
  cPARSE_FLOAT_MAX_ROW=200;
  // коэффициент масштабирования ширины столбцов грида и отчета
  cGRID_TO_EXCEL_SCALE=6;
  // максимальная ширина столбца
  cMAX_COLUMN_WIDTH=150;

  // формат Excel 97-2003
  cFORMAT_EXCEL_2003=56;
  // формат Word ( *.doc)
  cFORMAT_WORD_2003=0;


implementation

procedure SetColumnFloatFormat(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet :variant; Col, Row :integer; vArrayData: Variant);
var
  i,j :integer;
  k :real;
  vNumberFormat: string;
  vRange :variant;
begin
  for i:=0 to High(vOutCols) do
    begin
      if pDBGrid.Columns[vOutCols[i]].Field.DataType=ftFloat then
        begin
          vNumberFormat:=StringReplace(
            (pDBGrid.Columns[vOutCols[i]].Field as TFloatField).DisplayFormat,
            ',', DecimalSeparator,[rfReplaceAll]
          );
          vNumberFormat:=StringReplace(vNumberFormat,'.',
            DecimalSeparator,[rfReplaceAll]);
          if
            (
              (vNumberFormat<>'') and
              (
                // случай с "рублевым" форматом
                (vNumberFormat[Length(vNumberFormat)]='0') and
                // если формат содержит '.#' или ',#'
                (Pos(DecimalSeparator+'#',vNumberFormat)=0)
              )
            ) or
            (pDBGrid.DataSource.DataSet.RecordCount>cPARSE_FLOAT_MAX_ROW)
          then
            begin
              // добавляем '0' после запятой
              if (vNumberFormat='') then
                vNumberFormat:='# #0'+DecimalSeparator+'0####'
              else
                begin
                  // если в шаблоне нет разделителя разрядов, добавляем
                  if Pos('# ',vNumberFormat)=0 then vNumberFormat:='# '+vNumberFormat;
                  vNumberFormat:=StringReplace(
                    vNumberFormat,DecimalSeparator+'#',
                    DecimalSeparator+'0',[rfReplaceAll]
                  );
                  vNumberFormat:=StringReplace(
                    vNumberFormat,'#'+DecimalSeparator,
                    '0'+DecimalSeparator,[rfReplaceAll]
                  );
                end;
              try
                vRange:=vXLSheet.Range[
                    vXLSheet.Cells[Row,i+Col],
                    vXLSheet.Cells[pDBGrid.DataSource.DataSet.RecordCount+Row,i+Col]
                  ];
                vRange.Select;
                vRange.NumberFormat:=vNumberFormat;
              except
              end;
            end
          else
            begin
              for j:=0 to pDBGrid.DataSource.DataSet.RecordCount-1 do
                begin
                  try
                    k:=vArrayData[j,i];
                    if (k>Round(k)-1e-11) and (k<Round(k)+1e-11) then
                      vXLSheet.Cells[j+Row,i+Col].NumberFormat:='# #0'
                    else
                      vXLSheet.Cells[j+Row,i+Col].NumberFormat:='# #0'+DecimalSeparator+'####'
                  except
                  end;
                end;
            end;
        end;
    end;
    VarClear(vRange);
end;

procedure SetColumnFormat(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet: variant; Col, Row: integer);
var
  i :integer;
  vNumberFormat: string;
  vRange :variant;
begin
  for i:=0 to High(vOutCols) do
    begin
      vRange:=vXLSheet.Range[
        vXLSheet.Cells[Row,i+Col],
        vXLSheet.Cells[pDBGrid.DataSource.DataSet.RecordCount+Row,i+Col]
      ];
      vRange.Select;
      // у скрытых столбцов грида ширина = -1
      if pDBGrid.Columns[vOutCols[i]].Width>0 then
        begin
          if pDBGrid.Columns[vOutCols[i]].Width/cGRID_TO_EXCEL_SCALE>cMAX_COLUMN_WIDTH then
            vRange.ColumnWidth:=cMAX_COLUMN_WIDTH
          else
            vRange.ColumnWidth:=pDBGrid.Columns[vOutCols[i]].Width/cGRID_TO_EXCEL_SCALE;
        end;

      vNumberFormat:='';
      try
        case pDBGrid.Columns[vOutCols[i]].Field.DataType of
          ftSmallint, ftInteger, ftWord: vNumberFormat:='# #0';
          ftFloat: vNumberFormat:=''; // формат этого типа столбцов задается в процедуре SetColumnFloatFormat
          ftCurrency: vNumberFormat:='# #0.00#';
          ftDateTime, ftTimeStamp: vNumberFormat:='DD/MM/YYYY hh:mm:ss';
          ftDate: vNumberFormat:='DD/MM/YYYY';
          ftTime: vNumberFormat:='hh:mm:ss';
        else
          vNumberFormat:='@';
        end;
        if vNumberFormat<>'' then vRange.NumberFormat:=vNumberFormat;
      except
        try
          case pDBGrid.Columns[vOutCols[i]].Field.DataType of
            ftCurrency: vNumberFormat:='# #0,00#';
            ftDateTime, ftTimeStamp: vNumberFormat:='ДД.ММ.ГГГГ чч:мм:сс';
            ftDate: vNumberFormat:='ДД.ММ.ГГГГ';
            ftTime: vNumberFormat:='чч:мм:сс';
          else
            vNumberFormat:='@';
          end;
          if vNumberFormat<>'' then vRange.NumberFormat:=vNumberFormat;
        except
        end;
      end;
    end;
end;

procedure OutGrid(pDBGrid: TDBGrid; vOutCols: DynArrInt;
  vXLSheet: variant; Col, Row: integer);
var
  i,vRow :integer;
  vRange :Variant;
  // массив с выводимыми данными
  vArrayData: Variant;
begin
  if pDBGrid.DataSource.DataSet.RecordCount=0 then
    vXLSheet.Cells[Row, Col]:='В таблице нет данных!'
  else
    if High(vOutCols)>=0 then
      begin
        pDBGrid.DataSource.DataSet.DisableControls;
        // задаем типы столбцов
        SetColumnFormat(pDBGrid, vOutCols, vXLSheet, Col, Row);
        // создаем массив для формирования выводимых в Excel данных
        vArrayData:=VarArrayCreate(
          [0,pDBGrid.DataSource.DataSet.RecordCount-1,0,High(vOutCols)], varVariant
        );
        // сохраняем содержимое выбранных столбцов таблицы
        pDBGrid.DataSource.DataSet.First;
        vRow:=0;
        while not pDBGrid.DataSource.DataSet.Eof do
          begin
            for i:=0 to High(vOutCols) do
              vArrayData[vRow,i]:=pDBGrid.Columns[vOutCols[i]].Field.Value;
            pDBGrid.DataSource.DataSet.Next;
            Inc(vRow);
          end;
        vRange:=vXLSheet.Range[
          vXLSheet.Cells[Row+1,Col],
          vXLSheet.Cells[
            pDBGrid.DataSource.DataSet.RecordCount+Row,
            High(vOutCols)+Col
          ]
        ];
        // вставляем пустой диапазон
        vRange.Insert(xlShiftDown);
        // выделяем новый, вставленный диапазон пустых ячеек
        vRange:=vXLSheet.Range[
          vXLSheet.Cells[Row+1,Col],
          vXLSheet.Cells[
            pDBGrid.DataSource.DataSet.RecordCount+Row,
            High(vOutCols)+Col
          ]
        ];
        // выводим данные
        vRange.Value:=vArrayData;
        // форматируем вещественные столбцы,
        // Row - строка с заголовками столбцов, данные идут с Row+1
        SetColumnFloatFormat(pDBGrid, vOutCols, vXLSheet, Col, Row+1, vArrayData);
        // названия столбцов таблицы
        for i:=0 to High(vOutCols) do
          begin
            vXLSheet.Cells[Row,i+Col]:=
              pDBGrid.Columns[vOutCols[i]].Title.Caption;
          end;
        // выделяем всю таблицу
        vRange:=vXLSheet.Range[
          vXLSheet.Cells[Row,Col],
          vXLSheet.Cells[
            pDBGrid.DataSource.DataSet.RecordCount+Row,
            vRange.Column+High(vOutCols)
          ]
        ];
        // задаем границы для ячеек
        vRange.Select;
        vRange.Borders.LineStyle:=xlContinuous;
        vRange.Borders.Weight:=xlThin;
        vRange.Borders.ColorIndex:=xlAutomatic;
        // выделяем одну ячейку
        vRange:=vXLSheet.Range[
          vXLSheet.Cells[1,1],
          vXLSheet.Cells[1,1]
        ];
        vRange.Select;
        vOutCols:=nil;
        VarClear(vRange);
        VarClear(vArrayData);
        pDBGrid.DataSource.DataSet.EnableControls;
      end;
end;

function IsOffice2007(Version :string) :boolean;
begin
  { Номера версий:
    12.0 - Office 2007
    11.0 - Office 2003 }
  Result:=Pos('12.',Version)>0;
end;

function GetExcelExt(Version :string) :string;
begin
  if IsOffice2007(Version) then Result:='.xlsx'
    else Result:='.xls'
end;

function GetWordExt(Version :string) :string;
begin
  if IsOffice2007(Version) then Result:='.docx'
    else Result:='.doc'
end;

end.
