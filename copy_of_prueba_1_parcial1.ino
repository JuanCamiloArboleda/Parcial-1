//Arreglo donde posicion--> 0 = entrada serial(SER); 1 = reloj registro desplazamiento(RCLK); 2 = registro de salida(SRCLK);
int Array[3] = {2,4,5};

//matriz dinamica
int **matriz,*matriz_2;

//variables diversas para la implementacion
char tipo,fil,column,bol,bol_2;
char fil_2,column_2;
  
int entradas[4],num_patrones,num_patrones_2;
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
void imagen(int **m,int ma[]);

//funcion para segmentacion de columnas
void ParteCol(int **m,int col1,int col2, int col);

//funcion segmentacion de filas
void ParteFila(int **m,int col1,int col2, int col);

//funcion segmentacion de diagonales
void segmentacionDiagonales(int **m,int fila_1, int columna_1, int fila_2, int columna_2);

//funcion para inicializar matriz de n patrones
void inicializacion_matriz8*n(int **m,int n)

void setup()
{
  Serial.begin(9600);//numero de baudios
  
  
  Serial.println("Escoja si sera un solo patron o sera n patrones--> ");
  if(Serial.available())
  {
    bol = Serial.read();
    num_patrones_2 = bol-48;
    if(num_patrones_2 >1)
    {
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
            
    }
    else
    {
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
  
  delay(1000);
  
  LimpiarMatriz(matriz,8,8);
  Serial.println("opcion 1--> segmentacion fila ");
  Serial.println("opcion 2--> segmentacion columna ");
  Serial.println("opcion 4--> segmentacion de una diagonal ");
  Serial.println("opcion 3--> poner una posicion ");
  Serial.println("opcion 4--> mostrar en matriz de led ");  
  Serial.println(); 
}

void loop()
{    
  if(Serial.available())
  {
    Serial.print("Ingrese la opcion que desea hacer--> ");Serial.println();
   
    tipo = Serial.read();
    opcion = tipo - 48;
    if(opcion == 1)
    {
      Serial.print("entro a la opcion 1");Serial.println();
        if(Serial.available())
        {
          Serial.print("si entro");Serial.println();
          fil = Serial.read();
          entradas[0] = fil-48;
          if(Serial.available())
          {
            Serial.print("si entro");Serial.println();
            column = Serial.read();
          	entradas[1] = column - 48;
            if(Serial.available())
            {
              Serial.print("si entro");Serial.println();
              bol = Serial.read();
              entradas[2] = bol - 48;
              ParteFila(matriz,entradas[1],entradas[2],entradas[0]);
              MostrarMatriz(matriz,8,8);
              Serial.println();
            }     
          }
        }      
    }
    else if(opcion == 2)
    {   
        Serial.print("entro a la opcion 2 ");Serial.println();
        if(Serial.available())
        {
          Serial.print("si entro");Serial.println();
          fil = Serial.read();
          entradas[0] = fil-48;
          if(Serial.available())
          {
            Serial.print("si entro");Serial.println();
            column = Serial.read();
          	entradas[1] = column - 48;
            if(Serial.available())
            {
              Serial.print("si entro");Serial.println();
              bol = Serial.read();
              entradas[2] = bol - 48;
              ParteCol(matriz,entradas[1],entradas[2],entradas[0]);
              MostrarMatriz(matriz,8,8);
              Serial.println();
            }     
          }
        }     	
    }   
    else if(opcion == 3)
    {   
        Serial.print("entro a la opcion 3 ");Serial.println();
        if(Serial.available())
        {
          Serial.print("si entro");Serial.println();
          fil = Serial.read();
          entradas[0] = fil-48;
          if(Serial.available())
          {
            Serial.print("si entro");Serial.println();
            column = Serial.read();
          	entradas[1] = column - 48;
            if(Serial.available())
            {
              Serial.print("si entro");Serial.println();
              bol = Serial.read();
              entradas[2] = bol - 48;
              if(Serial.available())
              {
                Serial.print("si entro");Serial.println();
                bol_2 = Serial.read();
                entradas[3] = bol_2 - 48;
                segmentacionDiagonales(matriz,entradas[0], entradas[1],entradas[2],entradas[3]); 
                MostrarMatriz(matriz,8,8);
          		Serial.println();
              }
            }     
          }
        }     	
    }   
    else if(opcion == 4)
    {
      Serial.print("entro a la opcion 4,se ingresara un elemento en el espacio indicado de la matriz--> ");Serial.println();
      if(Serial.available())
      {   
        Serial.print("si entro");Serial.println();
        fil = Serial.read();
        entradas[0] = fil - 48;
        if(Serial.available())
        {  
          Serial.print("si entro");Serial.println();
          column = Serial.read();
          entradas[1] = column - 48;
          CambiarNumMatriz(matriz,entradas[0],entradas[1]);
          MostrarMatriz(matriz,8,8);
          Serial.println();
        } 
      } 
    }
    else if(opcion == 5)
    {
      Serial.print("entro--> entro--> ");
        imagen(matriz,Array);
        MostrarMatriz(matriz,8,8);       
    }
  Serial.println("opcion 1--> segmentacion fila ");
  Serial.println("opcion 2--> segmentacion columna ");
  Serial.println("opcion 4--> segmentacion de una diagonal ");
  Serial.println("opcion 3--> poner una posicion ");
  Serial.println("opcion 4--> mostrar en matriz de led ");  
  Serial.println(); 
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
    
  for(int i = 0; i<64; i++)
  {
    digitalWrite(2, 0);//se le da el valor para al serial el cual pasara el numero 

    digitalWrite(5, 0);//pin 5 nos da la opcion de desplazar el valor ingresado
    digitalWrite(5, 1);
    digitalWrite(5, 0);

    digitalWrite(4, 0);//pin 4 nos da la opcion de registrar el valor
    digitalWrite(4, 1);
    digitalWrite(4, 0);    
  }  
  
}

void CambiarNumMatriz(int **m,int nfilas, int ncolumnas)
{
  	*(*(m+(nfilas-1))+(ncolumnas-1)) = 1;//asignandole a la posicion de memoria el valor de uno
}

void imagen(int **m,int ma[])
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

void ParteCol(int **m,int col1,int col2, int col)
{
    for(int i=0;i<=7;i++)
    {
        for(int j=col1;j<=col2;j++)
        {
            
          *(*(m+(j-1))+(col-1)) = 1;
        }
    }
}

void ParteFila(int **m,int col1,int col2, int col){
    for(int i=0;i<=7;i++)
    {
        for(int j=col1;j<=col2;j++)
        {
            
          *(*(m+(col-1))+(j-1)) = 1;
        }
    }
}

void segmentacionDiagonales(int **m,int fila_1, int columna_1, int fila_2, int columna_2)
{
    
    fila_1--;fila_2--;columna_1--;columna_2--;

    if((fila_1<fila_2) && (columna_1>columna_2))
    {
        
      	*(*(m+fila_1)+columna_1) = 1;
        for(int i = fila_1+1; i<=fila_2;i++)
        {
            for(int j = 1; j!=0;columna_1--,j--)
            {

                
              *(*(m+i)+(columna_1 - 1)) = 1;
            }
        }
    }

    if((fila_1<fila_2) && (columna_1<columna_2))
    {
        *(*(m+fila_1)+columna_1) = 1;
        for(int i = fila_1+1; i<=fila_2;i++)
        {
            for(int j = 1; j!=0;j--,columna_1++)
            {
                
              *(*(m+i)+(columna_1 + 1)) = 1;
            }
        }
    }

    if((fila_1>fila_2)&&(columna_1<columna_2))
    {
        *(*(m+fila_1)+columna_1) = 1;
        for(int i = fila_1-1; i>=fila_2;i--)
        {
            for(int j = 0; j<1;j++,columna_1++)
            {
                
              *(*(m+i)+(columna_1 + 1)) = 1;
            }
        }
    }
    if((fila_1>fila_2)&&(columna_1>columna_2))
    {
        *(*(m+fila_1)+columna_1) = 1;
        for(int i = fila_1-1; i>=fila_2;i--)
        {
            for(int j = 0; j<1;j++,columna_1--)
            {
                
              *(*(m+i)+(columna_1 - 1)) = 1;
            }
        }
    }
}
  
