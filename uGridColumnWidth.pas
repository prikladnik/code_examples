unit uGridColumnWidth;

interface
uses Windows, cxGridTableView, cxGraphics, StrUtils, SysUtils,
  Variants, ShellAPI, cxCurrencyEdit;

const
  // ������������ ���������� "������ �����" �����, �� ����������� ������� ����� ���������� ������ �������
  MAX_ROW_ANALYSE_FOR_WIDTH = 10;
  // ���������� � ����������� ���������� ������ �������
  MIN_COL_WIDTH = 25;
  // ����������� ���������� ������ �������
  MAX_COL_WIDTH = 700;

  {
    ������������� ������ ��� ���� �������� tvCells.
    pCanvas - Canvas �����, � ������� ��������� �������
    pAnalyseAllRows - true, ���� ����� ���������� ������ �������� �� �����������
      ���� �����, � �� ������ ������ MAX_ROW_ANALYSE_FOR_WIDTH
    pTuneWidth - true, ���� ����� ��������� ������ �������� �� ����������� �����
      �������� TuneColumnsWidth
    pUseMaxColWidth - true, ���� ����� ������������ ������������ ������ �������
      ��������� MAX_COL_WIDTH
  }
  procedure SetColumnsWidth(tvCells: TcxGridTableView; pCanvas :TcxCanvas;
    pAnalyseAllRows :boolean=false; pTuneWidth :boolean=false;
    pUseMaxColWidth :boolean=true);
  { ����������� ������ ��� ������� �� tvCells c �������� pColIndex �� ��� ������
     pMaxRow �������.
    pCanvas - Canvas �����, � ������� ��������� ���� �������
  }
  function DefineColumnWidth(tvCells :TcxGridTableView;
    pColIndex, pMaxRow :integer; pCanvas: TcxCanvas;
    pUseMaxColWidth :boolean) :integer;
  {
    ���������� ������ ����� � tvCells ��� ���������� ������ �������� ���,
    ����� ����������� �������� ���������.
    pCanvas - Canvas �����, � ������� ��������� �������
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
    // ��������� ������ ��� ��������� �������
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
      // ��������� ������ ��� ������� ���� �����, ���� � �.�.
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
  // �������������� �������
  OperateColumns :array of array of integer;
begin
  if (tvCells.Site.Width > 0) then begin
    // �� ������ ����� �������� ������ ������������ ������ ���������
    if tvCells.Site.VScrollBarVisible then
      SumWidth := tvCells.Site.VScrollBar.Width
    else
      SumWidth := 0;
    // ��������� ����� ������ ������� ��������
    for i := 0 to tvCells.VisibleColumnCount - 1 do
      Inc(SumWidth, tvCells.VisibleColumns[i].Width);

    // �������� �� ��������� �����
    if (SumWidth < tvCells.Site.Width) then begin
      // ��������� ������ �� ������� ������� ��������
      SetLength(OperateColumns, tvCells.VisibleColumnCount);
      k := 0;
      for i := 0 to High(OperateColumns) do begin
        SetLength(OperateColumns[i], 3);
        OperateColumns[i, 0]:=i; // ����� �������
        // ������ ������� ��� ������� ��������� ����� ����� ���������
        d := pCanvas.TextWidth(tvCells.VisibleColumns[i].Caption + 'A');
        // �������� �� ���������� ����������� ���������� ������ �������
        if (d < MAX_COL_WIDTH) or (not pUseMaxColWidth) then
          OperateColumns[i, 2] := d
        else
          OperateColumns[i, 2] := MAX_COL_WIDTH;
        // ���� ��������� ������� ����� ���������
        if OperateColumns[i, 2] <= tvCells.VisibleColumns[i].Width then
          OperateColumns[i, 1] := 1 // ������ ������� �� ����� ������
        else
        begin
          OperateColumns[i, 1] := 0; // ������ � ���� ������� ����� ������
          Inc(k);
        end;
      end;

      // ������������� ������� ������������ ����� ����� ���������,
      // � ������� ��������� �� ����� ���������
      while (SumWidth < tvCells.Site.Width) and (k > 0) do
      begin
        if tvCells.Site.Width - SumWidth < k then
          m := tvCells.Site.Width - SumWidth
        else
          m := (tvCells.Site.Width - SumWidth) div k;
        i:=0;
        while (i <= High(OperateColumns)) and (SumWidth + m <= tvCells.Site.Width) do
        begin
          // ���� ������ ������� ����� ������
          if OperateColumns[i, 1] = 0 then begin
            // ���� ������������ ������ ������� ����� ������ ������
            if tvCells.VisibleColumns[i].Width + m > OperateColumns[i, 2] then
              d := OperateColumns[i, 2] - tvCells.VisibleColumns[i].Width
            else
              d := m;
            tvCells.VisibleColumns[i].Width := tvCells.VisibleColumns[i].Width + d;
            Inc(SumWidth, d);
            // ���������� �� ������ ������
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
    // ����������, ������� ����� ����� �������������
    if pAnalyseAllRows then
      pMaxRow := tvCells.DataController.RecordCount
    else
      pMaxRow := MAX_ROW_ANALYSE_FOR_WIDTH;
    // ������������� �������������� ������ ��������
    for i := 0 to tvCells.ColumnCount - 1 do
      tvCells.Columns[i].Width := DefineColumnWidth(tvCells, i, pMaxRow, pCanvas,
        pUseMaxColWidth);
    // ���������� ������ ����� ��� ������� ����������� ���������� ������
    if pTuneWidth then
      TuneColumnsWidth(tvCells, pCanvas, pUseMaxColWidth);
    tvCells.EndUpdate;
  end;
end;

end.
