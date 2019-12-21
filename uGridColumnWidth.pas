unit uGridColumnWidth;

interface
uses Windows, cxGridTableView, cxGraphics, StrUtils, SysUtils,
  Variants, ShellAPI, cxCurrencyEdit;

const
  // максимальное количество "первых строк" грида, по содержимому которых нужно определять ширину столбца
  MAX_ROW_ANALYSE_FOR_WIDTH = 10;
  // минимально и максимально допустимая ширина столбца
  MIN_COL_WIDTH = 25;
  // максимально допустимая ширина столбца
  MAX_COL_WIDTH = 700;

  {
    Устанавливает ширину для всех столбцов tvCells.
    pCanvas - Canvas грида, в котором находятся столбцы
    pAnalyseAllRows - true, если нужно определять ширину столбцов по содержимому
      всех строк, а не только первым MAX_ROW_ANALYSE_FOR_WIDTH
    pTuneWidth - true, если после установки ширины столбцов по содержимому нужно
      вызывать TuneColumnsWidth
    pUseMaxColWidth - true, если нужно ограничивать максимальную ширину столбца
      значением MAX_COL_WIDTH
  }
  procedure SetColumnsWidth(tvCells: TcxGridTableView; pCanvas :TcxCanvas;
    pAnalyseAllRows :boolean=false; pTuneWidth :boolean=false;
    pUseMaxColWidth :boolean=true);
  { Определение ширины для столбца из tvCells c индексом pColIndex по его первым
     pMaxRow строкам.
    pCanvas - Canvas грида, в котором находится этот столбец
  }
  function DefineColumnWidth(tvCells :TcxGridTableView;
    pColIndex, pMaxRow :integer; pCanvas: TcxCanvas;
    pUseMaxColWidth :boolean) :integer;
  {
    Использует пустое место в tvCells для увеличения ширины столбцов так,
    чтобы максимально показать заголовки.
    pCanvas - Canvas грида, в котором находятся столбцы
  }
  procedure TuneColumnsWidth(tvCells :TcxGridTableView; pCanvas: TcxCanvas;
    pUseMaxColWidth :boolean);

implementation

function DefineColumnWidth(tvCells :TcxGridTableView; pColIndex,
  pMaxRow :integer; pCanvas: TcxCanvas; pUseMaxColWidth :boolean) :integer;
var
  i :integer;
  Max :variant;
begin
  Result := MIN_COL_WIDTH;
  if not tvCells.Columns[pColIndex].Visible then Exit;
  try
    i := 0;
    // установка ширины для числового столбца
    if
      AnsiContainsText(
        'Currency;Float;Integer', tvCells.Columns[pColIndex].DataBinding.ValueType
      )
    then
    begin
      Max := 0;
      while (i < pMaxRow) and (i < tvCells.DataController.RecordCount) do begin
        if
          (not VarIsNull(tvCells.DataController.Values[i, pColIndex])) and
          (Abs(tvCells.DataController.Values[i, pColIndex]) > Abs(Max))
        then
          Max := tvCells.DataController.Values[i, pColIndex];
        Inc(i);
      end;
      if tvCells.Columns[pColIndex].Properties <> nil then
        Result := pCanvas.TextWidth(FormatFloat(
          TcxCurrencyEditProperties(tvCells.Columns[pColIndex].Properties).DisplayFormat,
          Max)
        )
      else
        Result := pCanvas.TextWidth(VarToStr(Max) + 'A');
    end else
    begin
      // установка ширины для столбца типа текст, дата и т.п.
      while (i < pMaxRow) and (i < tvCells.DataController.RecordCount) do
      begin
        if
          (not VarIsNull(tvCells.DataController.Values[i, pColIndex])) and
          (pCanvas.TextWidth(tvCells.DataController.Values[i, pColIndex]) > Result)
        then
          Result := pCanvas.TextWidth(tvCells.DataController.Values[i, pColIndex]);
        Inc(i);
      end;
    end;
    Inc(Result, pCanvas.TextWidth('A'));
    if Result < MIN_COL_WIDTH then
      Result := MIN_COL_WIDTH
    else
      if pUseMaxColWidth and (Result > MAX_COL_WIDTH) then
        Result := MAX_COL_WIDTH;
  except
  end;
end;

procedure TuneColumnsWidth(tvCells :TcxGridTableView; pCanvas: TcxCanvas;
  pUseMaxColWidth :boolean);
var
  i, d, k, m, SumWidth :integer;
  // обрабатываемые столбцы
  OperateColumns :array of array of integer;
begin
  if (tvCells.Site.Width > 0) then begin
    // из ширины грида вычитаем ширину вертикальной полосы прокрутки
    if tvCells.Site.VScrollBarVisible then
      SumWidth := tvCells.Site.VScrollBar.Width
    else
      SumWidth := 0;
    // вычисляем общую ширину видимых столбцов
    for i := 0 to tvCells.VisibleColumnCount - 1 do
      Inc(SumWidth, tvCells.VisibleColumns[i].Width);

    // проверка на свободное место
    if (SumWidth < tvCells.Site.Width) then begin
      // формируем массив из номеров видимых столбцов
      SetLength(OperateColumns, tvCells.VisibleColumnCount);
      k := 0;
      for i := 0 to High(OperateColumns) do begin
        SetLength(OperateColumns[i], 3);
        OperateColumns[i, 0]:=i; // номер столбца
        // ширина столбца при которой заголовок будет виден полностью
        d := pCanvas.TextWidth(tvCells.VisibleColumns[i].Caption + 'A');
        // проверка на превышение максимально допустимой ширины столбца
        if (d < MAX_COL_WIDTH) or (not pUseMaxColWidth) then
          OperateColumns[i, 2] := d
        else
          OperateColumns[i, 2] := MAX_COL_WIDTH;
        // если заголовок столбца виден полностью
        if OperateColumns[i, 2] <= tvCells.VisibleColumns[i].Width then
          OperateColumns[i, 1] := 1 // ширину столбца не нужно менять
        else
        begin
          OperateColumns[i, 1] := 0; // ширину в этом столбце нужно менять
          Inc(k);
        end;
      end;

      // распределение пустого пространства между всеми столбцами,
      // у которых заголовок не видно полностью
      while (SumWidth < tvCells.Site.Width) and (k > 0) do
      begin
        if tvCells.Site.Width - SumWidth < k then
          m := tvCells.Site.Width - SumWidth
        else
          m := (tvCells.Site.Width - SumWidth) div k;
        i:=0;
        while (i <= High(OperateColumns)) and (SumWidth + m <= tvCells.Site.Width) do
        begin
          // если ширину столбца нужно менять
          if OperateColumns[i, 1] = 0 then begin
            // если получившаяся ширина столбца будет больше нужной
            if tvCells.VisibleColumns[i].Width + m > OperateColumns[i, 2] then
              d := OperateColumns[i, 2] - tvCells.VisibleColumns[i].Width
            else
              d := m;
            tvCells.VisibleColumns[i].Width := tvCells.VisibleColumns[i].Width + d;
            Inc(SumWidth, d);
            // установили ли нужную ширину
            if tvCells.VisibleColumns[i].Width = OperateColumns[i, 2] then
            begin
              OperateColumns[i, 1] := 1;
              Dec(k);
            end;
          end;
          Inc(i);
        end;
      end;
      OperateColumns := nil;
    end;
  end;
end;

procedure SetColumnsWidth(tvCells: TcxGridTableView;
  pCanvas :TcxCanvas; pAnalyseAllRows :boolean; pTuneWidth :boolean;
  pUseMaxColWidth :boolean);
var
  i, pMaxRow :integer;
begin
  if tvCells.DataController.RecordCount > 0 then
  begin
    tvCells.BeginUpdate;
    // определяем, сколько строк будем анализировать
    if pAnalyseAllRows then
      pMaxRow := tvCells.DataController.RecordCount
    else
      pMaxRow := MAX_ROW_ANALYSE_FOR_WIDTH;
    // устанавливаем первоначальную ширину столбцов
    for i := 0 to tvCells.ColumnCount - 1 do
      tvCells.Columns[i].Width := DefineColumnWidth(tvCells, i, pMaxRow, pCanvas,
        pUseMaxColWidth);
    // используем пустое место для полного отображения заголовков таблиц
    if pTuneWidth then
      TuneColumnsWidth(tvCells, pCanvas, pUseMaxColWidth);
    tvCells.EndUpdate;
  end;
end;

end.
