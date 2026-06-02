Attribute VB_Name = "Module2"
' Se agregan las variables
Public Function Iterar(Potencia As Double, Voltaje As Double, Limite As Double) As Double
    Dim i As Double
    Dim resultado As Double
    
    For i = 1 To 10000
        resultado = (Voltaje / (2 ^ Potencia)) * i
        If resultado >= Limite Then
            Iterar = i
            Exit Function
        End If
    Next i
    Iterar = 0 'No se alcanzo el limite en 100 iteraciones
End Function
