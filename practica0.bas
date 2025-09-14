Attribute VB_Name = "Module1"
Option Explicit

' Codigo para generar todas las combinaciones posibles
' dando la opcion de escoger cuantos dados usar (1 - 5)
' y calcular la suma de sus caras.
Sub Combinaciones()
    Dim ws As Worksheet
    Dim i As Long, j As Long, k As Long, l As Long, m As Long
    Dim fila As Long
    Dim nDados As Integer
    Dim suma As Integer

    ' Consulta el numero de dados
    nDados = InputBox("¿Cuantos dados quieres enumerar? (1 a 5)", "Numero de dados", 2)
    If nDados < 1 Or nDados > 5 Then
        MsgBox "Solo se permite entre 1 y 5"
        Exit Sub
    End If
    
    ' Crear hoja nueva o limpiar si ya existe
    On Error Resume Next
    Set ws = ThisWorkbook.Sheets("Combinaciones")
    If ws Is Nothing Then
        Set ws = ThisWorkbook.Sheets.Add
        ws.Name = "Combinaciones"
    Else
        ws.Cells.Clear
    End If
    On Error GoTo 0
    
    fila = 2
    
    ' Encabezados
    For i = 1 To nDados
        ws.Cells(1, i).Value = "Dado " & i
    Next i
    ws.Cells(1, nDados + 1).Value = "Suma"

    ' Generar combinaciones de 1 a 5 dados
    For i = 1 To 6
        If nDados = 1 Then
            suma = i
            ws.Cells(fila, 1).Value = i
            ws.Cells(fila, 2).Value = suma
            fila = fila + 1
        Else
        For j = 1 To 6
            If nDados = 2 Then
                suma = i + j
                ws.Cells(fila, 1).Value = i
                ws.Cells(fila, 2).Value = j
                ws.Cells(fila, 3).Value = suma
                fila = fila + 1
            Else
            For k = 1 To 6
                If nDados = 3 Then
                    suma = i + j + k
                    ws.Cells(fila, 1).Value = i
                    ws.Cells(fila, 2).Value = j
                    ws.Cells(fila, 3).Value = k
                    ws.Cells(fila, 4).Value = suma
                    fila = fila + 1
                Else
                For l = 1 To 6
                    If nDados = 4 Then
                        suma = i + j + k + l
                        ws.Cells(fila, 1).Value = i
                        ws.Cells(fila, 2).Value = j
                        ws.Cells(fila, 3).Value = k
                        ws.Cells(fila, 4).Value = l
                        ws.Cells(fila, 5).Value = suma
                        fila = fila + 1
                    Else
                    For m = 1 To 6
                        If nDados = 5 Then
                            suma = i + j + k + l + m
                            ws.Cells(fila, 1).Value = i
                            ws.Cells(fila, 2).Value = j
                            ws.Cells(fila, 3).Value = k
                            ws.Cells(fila, 4).Value = l
                            ws.Cells(fila, 5).Value = m
                            ws.Cells(fila, 6).Value = suma
                            fila = fila + 1
                        End If
                    Next m
                    End If
                Next l
                End If
            Next k
            End If
        Next j
        End If
    Next i
    
    MsgBox "¡Combinaciones generadas en la hoja 'Combinaciones'!"
End Sub

' ==========Frecuencias==============
' Creacion de las tablas de frecuencia para graficar

Sub TFrecuencia()
    Dim ws As Worksheet, ws2 As Worksheet
    Dim uFila As Long, i As Long
    Dim colSuma As Long
    Dim ultimaFilaFrecuencia As Long
    
    ' Hoja de combinaciones
    Set ws = ThisWorkbook.Sheets("Combinaciones")
    uFila = ws.Cells(ws.Rows.Count, 1).End(xlUp).Row
    
    ' Detectar columna de las sumas (ultima columna usada en la fila 1)
    colSuma = ws.Cells(1, ws.Columns.Count).End(xlToLeft).Column
    
    ' Crear hoja "Graficas" o limpiarla si ya existe
    On Error Resume Next
    Set ws2 = ThisWorkbook.Sheets("Graficas")
    If ws2 Is Nothing Then
        Set ws2 = ThisWorkbook.Sheets.Add
        ws2.Name = "Graficas"
    Else
        ws2.Cells.Clear
    End If
    On Error GoTo 0
    
    ' Copiar columna de sumas a la nueva hoja
    ws.Range(ws.Cells(2, colSuma), ws.Cells(uFila, colSuma)).Copy
    ws2.Range("A2").PasteSpecial xlPasteValues
    
    ' Encabezados
    ws2.Cells(1, 1).Value = "Suma"
    ws2.Cells(1, 2).Value = "Frecuencia"
    
    ' Quitar duplicados y ordenar
    ws2.Range("A2", ws2.Range("A2").End(xlDown)).RemoveDuplicates Columns:=1, Header:=xlNo
    ws2.Range("A2", ws2.Range("A2").End(xlDown)).Sort Key1:=ws2.Range("A2"), Order1:=xlAscending
    
    ' Contar frecuencias
    ultimaFilaFrecuencia = ws2.Cells(ws2.Rows.Count, 1).End(xlUp).Row
    For i = 2 To ultimaFilaFrecuencia
        ws2.Cells(i, 2).Value = Application.WorksheetFunction.CountIf(ws.Range(ws.Cells(2, colSuma), ws.Cells(uFila, colSuma)), ws2.Cells(i, 1).Value)
    Next i
    
    ' Crear grafico de columnas
    Dim grafico As ChartObject
    Set grafico = ws2.ChartObjects.Add(Left:=300, Width:=400, Top:=10, Height:=300)
    With grafico.Chart
        .ChartType = xlColumnClustered
        .SetSourceData Source:=ws2.Range("A1:B" & ultimaFilaFrecuencia)
        .HasTitle = True
        .ChartTitle.Text = "Distribucion de las Sumas"
        .Axes(xlCategory).HasTitle = True
        .Axes(xlCategory).AxisTitle.Text = "Suma"
        .Axes(xlValue).HasTitle = True
        .Axes(xlValue).AxisTitle.Text = "Frecuencia"
    End With
    
    MsgBox "Tabla de frecuencia y grafico creados en la hoja 'Graficas'."
End Sub


'========Graficos=============

Sub Graficos()
    Dim ws As Worksheet
    Dim chartObj As ChartObject
    Dim uFila As Long
    Dim tituloGrafico As String
    Dim s As Series
    
    ' Hoja de datos
    On Error Resume Next
    Set ws = ThisWorkbook.Sheets("Graficas")
    On Error GoTo 0
    If ws Is Nothing Then
        MsgBox "Primero debes generar la tabla de frecuencia (hoja 'Graficas').", vbExclamation
        Exit Sub
    End If
    
    ' Borrar graficos anteriores
    For Each chartObj In ws.ChartObjects
        chartObj.Delete
    Next chartObj
    
    ' ultima fila con datos
    uFila = ws.Cells(ws.Rows.Count, 1).End(xlUp).Row
    If uFila < 2 Then
        MsgBox "No hay datos en A2:B...", vbExclamation
        Exit Sub
    End If
    
    ' Titulo dinamico usando la variable global gNumDados
    If gNumDados >= 1 Then
        If gNumDados = 1 Then
            tituloGrafico = "Distribucion de la suma de 1 dado"
        Else
            tituloGrafico = "Distribucion de la suma de " & gNumDados & " dados"
        End If
    Else
        tituloGrafico = "Distribucion de las sumas"
    End If
    
    ' Crear grafico con UNA SOLA SERIE (frecuencia)
    Set chartObj = ws.ChartObjects.Add(Left:=250, Top:=50, Width:=500, Height:=300)
    With chartObj.Chart
        .ChartType = xlColumnClustered
        ' borrar series previas por seguridad
        Do While .SeriesCollection.Count > 0
            .SeriesCollection(1).Delete
        Loop
        
        Set s = .SeriesCollection.NewSeries
        s.Name = "Frecuencia"
        s.Values = ws.Range("B2:B" & uFila)   ' Y = frecuencias (solo la naranja)
        s.XValues = ws.Range("A2:A" & uFila)  ' X = sumas
        
        ' Color naranja
        On Error Resume Next
        s.Format.Fill.Solid
        s.Format.Fill.ForeColor.RGB = RGB(255, 165, 0)
        On Error GoTo 0
        
        .HasTitle = True
        .ChartTitle.Text = tituloGrafico
        .Axes(xlCategory).HasTitle = True
        .Axes(xlCategory).AxisTitle.Text = "Suma"
        .Axes(xlValue).HasTitle = True
        .Axes(xlValue).AxisTitle.Text = "Frecuencia"
        
        ' Eliminar leyenda (opcional)
        On Error Resume Next
        .Legend.Delete
        On Error GoTo 0
    End With
    
    MsgBox "Grafico (solo frecuencias) generado en la hoja 'Graficas'."
End Sub






