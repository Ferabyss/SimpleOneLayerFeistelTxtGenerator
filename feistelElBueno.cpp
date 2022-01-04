//Este programa utiliza un archivo de texto 
//proporcionado por el usuario y regresa otro 
//archivo de texto con el contenido cifrado y/o descifrado
#include <iostream>
#include <fstream>
using namespace std;

int encode(unsigned char c,int K0) {
                        //ej. c= 0011 1001
    int L0 = c >> 4;    // obtiene el lado izq del byte
                        // 0000 0011 
    int R0 = ((c & 15) << 4) >> 4 ; // obtiene el lado derecho y lo recorre
                        //1001 0000 -> 0000 1001 
    int F0 = K0 ^ R0;   // Aplica la función (en esta cosa una xor)
                        //entre la llave y R0
    int R1 = L0 ^ F0;
                        // XOR default entre F0 y el lado izq.
    int L1 =  R0 << 4;  // Pasa el lado derecho al izq.
                        //0000 1001 -> 1001 0000
    return L1 + R1;
}

int decode(unsigned char c, int K0) {

    int L1 = c >> 4;    // lado izq
    int R1 = ((c & 15) << 4) >> 4 ; // lado derecho
    int F0 = K0 ^ L1;   //función inversa con la llave
    int L0 = (R1 ^ F0) << 4;//Se obtienen los 4 bits y se recorren a la izq.
    int R0 = L1;
    
    return L0 + R0;
}

int main() { 
    string tex,texto;
    char c;
    int r, descypher, cypher, K0;
    cout<<"\n||BIENVENIDO||\nFavor de nombrar al archivo txt con el que desea ejecutar este programa como 'texto'\n\n||AVISO||\nVerificar que NO tenga ningun archivo llamado 'cifrado.txt' o descifrado.txt, pues no se desea sobreescribir algun archivo importante para usted, gracias."<<endl;
    cout<<"\nIngrese una llave entre 0 y 15: ";
    cin>>K0;

    while(K0>15||K0<0){
        cout<<"\nPORFAVOR DIGITE UNA LLAVE VALIDA";
        cout<<"\n\nIngrese una llave entre 0 y 15: ";
        cin>>K0;
    }
    


    cout<<"\n1-> Cifrar\n2-> Descifrar\n3-> Ambos\n\nElija una opción: ";
    cin>>r;

    while(r>3||r<1){
        cout<<"\nPORFAVOR DIGITE UNA OPCION VALIDA";
        cout<<"\n\n1-> Cifrar\n2-> Descifrar\n3-> Ambos\n\nElija una opción: ";
        cin>>r;
        }

    
    ifstream input;//buffer de entrada (solo lectura)
    try{input.open("texto.txt");
        
        if(!input.is_open()){
            ofstream tmp("texto.txt");//abre un buffer temporal para
            tmp<<"Texto default";      // crear un archivo default
            tmp.close();

            input.open("texto.txt");
        //genera una excepcion que puede entender catch a falta de errores predefinidos
            throw("\nNO SE DETECTO UN ARCHIVO 'texto.txt', pero se creo un archivo con contenido default,\nmodifique 'texto.txt' con el texto que desee y vuelva a correr el programa\n");
            } 
        }
    catch(const char* e){
        cout<<e<<endl;}
   

    while(getline(input,tex)){//obtiene todas la lineas del txt
        texto+=(tex+'\n');    //coloca un salto cada que hay un salto
        };                    //y lo guarda en la variable 'texto'
    input.close();
    remove("cifrado.txt");//elimina los archivos de 
    remove("descifrado.txt");//pruebas anteriores
                            //(solo para mayor comodidad)                         



    //Opcion solo cifrar
    if(r==1){
        ofstream archivo("cifrado.txt");//abre un buffer 
                                        //y crea un archivo .txt
        for (int i = 0; i<texto.length(); i++){
            c = texto[i];
            cypher = encode(c,K0);      //aplica la función de cifrado a cada  
                                        //caracter del string
            archivo << (char)cypher;//escribe en el txt el caracter cifrado
            }
        archivo.close();//cierra el buffer
        }



    //Opcion solo descifrar
    else if(r==2){
        ofstream archivo2("descifrado.txt");
        for (int i = 0; i<(texto.length()-1); i++){//se le resta uno para omitir
                                                    // el ultimo salto de linea (vea linea 46)
            c = texto[i];
            descypher = decode(c,K0);//aplica la función de descifrado a cada  
                                        //caracter del string
            archivo2 << (char)descypher;//escribe el caracter descifrado
            }
        archivo2.close();//cierra el buffer
        }



//Opcion cifrar y descifrar
  else if(r==3){
      
      ofstream archivo("cifrado.txt");//abre los buffers
      ofstream archivo2("descifrado.txt");
      
      for (int i = 0; i<texto.length(); i++){
          
          c = texto[i];
          cypher = encode(c,K0);        //cifra
          descypher = decode(cypher,K0);//descifra 
          
          archivo << (char)cypher;      //guarda cada caracter en el txt de cifrado
          archivo2 << (char)descypher; //guarda en el txt de descifrado
          }
      
      archivo.close();//cierra los buffers
      archivo2.close();
      }
    }