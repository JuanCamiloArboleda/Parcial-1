//Arreglo donde posicion--> 0 = entrada serial(SER); 1 = reloj registro desplazamiento(RCLK); 2 = registro de salida(SRCLK);
int Array[3] = {2,4,5};

//matriz dinamica
int **matriz;

//variables diversas para la implementacion
char tipo,fil,column,bol;
char fil_2,column_2;
  
int entradas[2];
int num_columna = 0,auxiliar = 0,opcion = 0;

//funcion que recibe 4 variables tipo int, la primera el valor que se le dara a cada led y las siguientes los puertos analogos del arduino
void Verificacion(int ma[]);

//funcion que muestra la matriz
void MostrarMatriz(int **m,int nfilas,int ncolumnas);

//funcion ingresar valores a la matriz
void CambiarNumMatriz(int **m,int nfilas, int ncolumnas);

//funcion que limpia la matriz
void LimpiarMatriz(int **m,int nfilas,int ncolumnas);

//la funcion que permitira que la matriz de led se vizualice
void recorrer(int **m,int ma[]);

//rellenar columna
void Columna(int **m,int col);

//rellenar una fila
void Fila(int **m,int fila);

//imprimir la matriz identidad
void DiagonalMatriz(int **m);

//imprimir la matriz identidad inversa
void DiagonalMatrizInversa(int **m);

void setup()
{
  Serial.begin(9600);//numero de baudios
  
  matriz = new int*[8];//reservando memoriapara la matriz
  
  for(int i = 0; i<8; i++)
  {
    matriz[i] = new int[8];   //reservando la memoria 
  }
  
  for(int i = 0; i<8;i++)//rellenando la matriz de ceros
  {
   	for(int j = 0; j<8;j++)
    {
      *(*(matriz+i)+j) = 0;      
    }
  }
   
  //configuracion de puertos digitales de forma: OUTPUT
  pinMode(Array[0], OUTPUT);
  pinMode(Array[1], OUTPUT);
  pinMode(Array[2], OUTPUT);
  
  //inicializar la entrada serial y los relojes en bajo
  digitalWrite(Array[0], 0);
  digitalWrite(Array[1], 0);
  digitalWrite(Array[2], 0);
  
  Serial.print("Se le mostrara que la matriz de LEDS sirve--> ");Serial.println();
  Verificacion(Array);
  
  MostrarMatriz(matriz,8,8);
  Serial.println("opcion 1--> rellenar toda una columna ");
  Serial.println("opcion 2--> rellenar toda una fila ");
  Serial.println("opcion 3--> rellenar diagonal principal ");
  Serial.println("opcion 4--> rellenar diagonal principal inversa ");
  Serial.println("opcion 4--> poner una posicion ");
  
}


void loop()
{   
  
  /*
	if(Serial.available())
  	{    
      auxiliar++;
      if(auxiliar == 1)
      {
        fil = Serial.read();
        entradas[0] = fil - 48;

      }
      else if(auxiliar == 2)
      {
        column = Serial.read();
        entradas[1] = column - 48;
        CambiarNumMatriz(matriz,entradas[0],entradas[1]);
        MostrarMatriz(matriz,8,8);
      } 
      else if(auxiliar == 3)
      {
        auxiliar = 0;
        bol = Serial.read();
        if(bol == 'o')
        {
          recorrer(matriz,Array);        
        }            
      }
    }
    */
  
  if(Serial.available())
  {
    Serial.print("Ingrese la opcion que desea hacer--> ");Serial.println();
   
    tipo = Serial.read();
    opcion = tipo - 48;
    
    if(opcion == 1)
    {
      Serial.print("entro a la opcion 1,ingrese el numero de la columna--> ");Serial.println();
      if(Serial.available())
      {    
        column_2 = Serial.read();
        num_columna = column_2 - 48;
		Columna(matriz,num_columna); 
        MostrarMatriz(matriz,8,8);
        Serial.println();
      }      
    }
    else if(opcion == 2)
    {
      Serial.print("entro a la opcion 2,ingrese el numero de la fila--> ");Serial.println();
      if(Serial.available())
      {    
        fil_2 = Serial.read();
        num_columna = fil_2 - 48;
		Fila(matriz,num_columna);
        MostrarMatriz(matriz,8,8);
        Serial.println();
      }      
    }
    else if(opcion == 3)
    {
      Serial.print("entro a la opcion 3,se ingresara la diagonal principal--> ");Serial.println();
      void DiagonalMatriz(int **m); 
      MostrarMatriz(matriz,8,8);
      Serial.println();
    }
    else if(opcion == 4)
    {
      Serial.print("entro a la opcion 4,se ingresara la diagonal principal inversa--> ");Serial.println();
      void DiagonalMatrizInversa(int **m);
      MostrarMatriz(matriz,8,8);
      Serial.println();
    }
    else if(opcion == 5)
    {
      Serial.print("entro a la opcion 5,se ingresara un elemento en el espacio indicado de la matriz--> ");Serial.println();
      if(Serial.available())
      {    
        fil = Serial.read();
        entradas[0] = fil - 48;
        if(Serial.available())
        {    
          column = Serial.read();
          entradas[1] = column - 48;
          CambiarNumMatriz(matriz,entradas[0],entradas[1]);
          MostrarMatriz(matriz,8,8);
          Serial.println();
        } 
      }      
    }
    Serial.println("opcion 1--> rellenar toda una columna ");
    Serial.println("opcion 2--> rellenar toda una fila ");
    Serial.println("opcion 3--> rellenar diagonal principal ");
    Serial.println("opcion 4--> rellenar diagonal principal inversa ");
    Serial.println("opcion 4--> poner una posicion ");
    Serial.println();Serial.println();
 }
  
}

void Verificacion(int ma[])
{
  for(int i = 0; i<64; i++)
  {
    digitalWrite(ma[0], 1);//se le da el valor para al serial el cual pasara el numero 

    digitalWrite(ma[2], 0);//pin 5 nos da la opcion de desplazar el valor ingresado
    digitalWrite(ma[2], 1);
    digitalWrite(ma[2], 0);

    digitalWrite(ma[1], 0);//pin 4 nos da la opcion de registrar el valor
    digitalWrite(ma[1], 1);
    digitalWrite(ma[1], 0);    
  }
}

void MostrarMatriz(int **m,int nfilas,int ncolumnas)
{
    Serial.print("Imprimiendo matriz inicial: ");Serial.println();
    for (int i=0;i<nfilas;i++)
    {
    	for (int j=0;j<ncolumnas;j++)
        {
          Serial.print('[');
          Serial.print(*(*(m+i)+j));
          Serial.print(']');
        }
      	Serial.println();
    }
}

void LimpiarMatriz(int **m,int nfilas,int ncolumnas)
{
    for (int i=0;i<nfilas;i++)
    {
        for (int j=0;j<ncolumnas;j++)
        {
            *(*(m+i)+j) = 0;
        }        
    }
}

void CambiarNumMatriz(int **m,int nfilas, int ncolumnas)
{
  	*(*(m+(nfilas-1))+(ncolumnas-1)) = 1;//asignandole a la posicion de memoria el valor de uno
}

void recorrer(int **m,int ma[])
{
  for(int i = 7;i>=0;i--)
  {
    for(int j = 7;j>=0;j--)
    {
      digitalWrite(ma[0], *(*(m+i)+j));//se le da el valor para al serial el cual pasara el numero 
  
      digitalWrite(ma[2], 0);
      digitalWrite(ma[2], 1);
      digitalWrite(ma[2], 0);

      digitalWrite(ma[1], 0);
      digitalWrite(ma[1], 1);
      digitalWrite(ma[1], 0);      
    }    
  }   
}

void Columna(int **m,int col)
{
    for(int i=0;i<=8;i++)
    {
        for(int j=0;j<=8;j++)
        {
            if (j==col-1)
            {
                *(*(m+i)+j)=1;
            }
        }
    }
}

void Fila(int **m,int fila){

    for(int i=0;i<=8;i++)
    {
        m[fila-1][i]=1;
    }
}

void DiagonalMatriz(int **m)
{   
  	for(int i = 0;i<8;i++)
    {
        *(*(m+i)+i)=1;
    }
}

void DiagonalMatrizInversa(int **m){
    for (int i = 0,j = 7;i<8;i++)
    {
        *(*(m+i)+(j-i))=1;
    }
}