
    #include <fstream>

    #include <iostream>

    #include <cstdio>

    #include <cstdlib>
    #include <cmath>
    using namespace std;
    ofstream myfile;
    ofstream myfile2;
    ofstream myfile3;

    int vector[12] = { 5,10,96,30,2,63,85,47,20,3,4,19};
    int vectorArbol[20] = {};
int getPosicion(int numBuscado){
    for(int i=0;i<(sizeof(vectorArbol)/sizeof(*vectorArbol));i++){
        if(vectorArbol[i]==numBuscado){
            return i;
        }
    }
}

//biscelar
void biselar(int nuevoValor){
    cout<<"proximamente!";
        
    // while(getPosicion(nuevoValor)!=1){
    //     //mientras no sea la cabeza
    // }
}
void recorrer(){
    cout<<"Recorrer \n";
    for(int i=0;i<(sizeof(vectorArbol)/sizeof(*vectorArbol));i++){
        cout<<"En "<<i<<": ";        
        cout<<vectorArbol[i];        
        cout<<"\n";        
    }    
}
void der(int num){
    //obtengo posicion de quien quiero subir
    int pActual = num;
    //hijo izquierdo
    int posHijoIzq = (pActual*2);
    int pPadre = trunc(pActual/2);
    int posHijoIzqDer = ((posHijoIzq*2)+1);
    int valorActual = vectorArbol[pActual];
    int valorPadre = vectorArbol[pPadre];
    int valorHijoIzq = vectorArbol[posHijoIzq];
    int valorHijoIzqder = vectorArbol[posHijoIzqDer];
    if(vectorArbol[posHijoIzq]!=0){
        //le asigno al padre en su izq el hijo derecho
        vectorArbol[posHijoIzq] = valorHijoIzqder;
        if(valorHijoIzqder!=0){
            vectorArbol[pActual] = valorActual;
            vectorArbol[pActual]= valorPadre;
        }

    }
    //si no existe padre
    if(vectorArbol[pPadre]==0){
        vectorArbol[1]=vectorArbol[posHijoIzq];
        //Si soy el izquierdo de mi padre
    }else if(vectorArbol[pPadre*2]==vectorArbol[pActual]){
        vectorArbol[pPadre*2] = vectorArbol[posHijoIzq];
    }else{
        //sino lo meto en la derecha
        vectorArbol[((pPadre*2)+1)] = vectorArbol[posHijoIzq];
    }
    // if(vectorArbol[posHijoIzq]!=0){
        int nuevaPos = getPosicion(valorHijoIzqder);
        vectorArbol[nuevaPos*2]=vectorArbol[pActual];
        nuevaPos = getPosicion(valorPadre);
        vectorArbol[nuevaPos] = valorHijoIzq;
    // }
}
void izq(int x){
    int pActual = x;
    int posActualHijoDer = (pActual*2)+1;
    int pPadre = trunc(pActual/2);
    int valorActual = vectorArbol[pActual];
    int valorHijoDer = vectorArbol[posActualHijoDer];
    int valorHijoDerIzq = vectorArbol[posActualHijoDer*2];
    int vPadre = vectorArbol[pPadre];
    if(vectorArbol[posActualHijoDer]!=0){
        //tu hijo derecho deberia ser el izquierdo de tu hijo derecho
        int nuevaPos = getPosicion(valorHijoDer);
        vectorArbol[nuevaPos] = valorHijoDerIzq;
        nuevaPos = getPosicion(valorHijoDer);

        if(valorHijoDerIzq!=0) vectorArbol[nuevaPos]=valorActual;
        vectorArbol[pActual]= vPadre;
    }
    if(vectorArbol[pPadre]==0){
        vectorArbol[1]=valorHijoDer;
        //si soy el hijo izquierdo
    }else if(vectorArbol[((pPadre*2)+1)]==vectorArbol[pActual]){
        int nuevaPos = getPosicion(valorActual);
        vectorArbol[nuevaPos]=valorHijoDer;
    }else{
        int nuevaPos = getPosicion(vPadre);
        vectorArbol[(nuevaPos*2)]=valorHijoDer;
    }
    int nuevaPos = getPosicion(valorHijoDer);
    if(valorHijoDer!=0)vectorArbol[nuevaPos*2]=valorActual;
    nuevaPos = getPosicion(vPadre);
    vectorArbol[nuevaPos] = valorActual;
    
}
void splay (int x){
    int posActual = x;

    int valor = vectorArbol[x];
    int posPadre = trunc(posActual/2);
    int posAbuelo = trunc(posPadre/2);
    while(posPadre!=0){
        if(vectorArbol[posAbuelo]!=0){
            if(vectorArbol[(posPadre*2)]==vector[posActual]){
                der(posPadre);
            }else{
                izq(posPadre);
            }
        }else if(vectorArbol[(posPadre*2)]==vector[posActual] && vectorArbol[(posAbuelo*2)]==vector[posPadre]){
            der(posAbuelo);
            der(posPadre);
        }else if(vectorArbol[((posPadre*2)+1)]==vectorArbol[posActual] && vectorArbol[((posAbuelo*2)+1)]==vectorArbol[posPadre]){
            izq(posAbuelo);
            izq(posPadre);
        }else if(vectorArbol[(posPadre*2)]==vectorArbol[posActual] && vectorArbol[((posAbuelo*2)+1)]==vectorArbol[posPadre]){
            der(posPadre);
            izq(posPadre);
        }else{
            izq(posPadre);
            der(posPadre);
        }
        posActual = getPosicion(valor);
        posPadre = trunc(posActual/2);
        posAbuelo = trunc(posPadre/2);
    }
}


void insertar(int nuevoValor){
    int raiz = vectorArbol[1];
    int numBuscador = 1;
    int padre = 0;
    int z = 1;
    // while(true){
        //Si es mayor
        while(vectorArbol[z]!=0){
            padre=z;
            if(vectorArbol[z]<nuevoValor){
                z = (z*2)+1;
            }else{
                z = z*2;
            }
        }
        //seteamos el nuevo valor
        vectorArbol[z]=nuevoValor;
        splay(z);
        recorrer();
}






int main()

    {

        // SplayTree st;

        


        // root = NULL;

        // const int length = 12;

        // int i;

        // for(i = 0; i < length; i++){
        //     root = st.Insert(vector[i], root);
        // }

        // cout<<"\nInOrder: \n";
        // // contadorParaVectorNuevo=-1;

        // st.InOrder(root);

        int input, choice;

        while(1)

        {
        cout<<"En el arreglo\n";
            for (int i=0;i<12;i++) {
              cout<<vector[i];
              if((i+1)!=12)
              cout<<",";
            }
              cout<<"\n";
          
          
          // myfile << "Writing this to a file.\n";
          
        //   cout<<"En el arbol vector\n";
        //   int limite = (sizeof(vectorArbol)/sizeof(*vectorArbol)) ;
        //   int indicador = 0;
        //   myfile2.open ("array.dot");
        //   myfile2 << "digraph { subgraph{ ";
        //     for (int i=0;i<limite;i++) {
        //       if(indicador==vectorArbol[i]){break;}
             
        //       if(i>0){
        //           myfile2 <<"v";
        //           myfile2 <<vectorArbol[i-1];
        //           myfile2 <<" -> "; 
        //           myfile2 <<"v";
        //           myfile2 <<vectorArbol[i];
        //           myfile2 <<";";
        //       }
        //       cout<<vectorArbol[i];
        //       indicador=vectorArbol[i];
        //       if((i+1)!=12)
        //       cout<<",";
        //     }
        //     myfile2 << "}}";
        //     myfile2.close();
           
  
        //     myfile3.open("arbolEnArray.dot");
        //     myfile3 << "digraph { subgraph{ ";
        //     // recorrerxNivel(root);
        //     myfile3 << "}}";
        //     myfile3.close();
        //     system("dot -Tpng arbolEnArray.dot -o arbolEnArray.png");
        //       cout<<"\n";

            cout<<"\nOpciones\n";

            cout<<"1. Agregar "<<endl;

            cout<<"2. Borrar"<<endl;

            cout<<"3. Buscar"<<endl;

            cout<<"4. Salir"<<endl;

            cout<<"Elija una opcion: ";

            cin>>choice;

            switch(choice)

            {

            case 1:

                cout<<"Ingrese el valor desea insertar: ";

                cin>>input;
                insertar(input);
                // recorrer();
                // root = st.Insert(input, root);

                // cout<<"\nDespues de inseretar: "<<input<<endl;
                // contadorParaVectorNuevo=-1;
                // myfile.open ("splay.dot");
                // myfile << "digraph { subgraph{ ";
                // st.InOrder(root);
                // myfile << "}}";
                // myfile.close();
                // system("dot -Tpng splay.dot -o splay.png");
                break;

            case 2:

                cout<<"Ingrese el valor a eliminar: ";

                cin>>input;

                // root = st.Delete(input, root);

                // cout<<"\nAfter Delete: "<<input<<endl;
                // contadorParaVectorNuevo=-1;
                // myfile.open ("splay.dot");
                // myfile << "digraph { subgraph{ ";
                // st.InOrder(root);
                // myfile << "}}";
                // myfile.close();
                // system("dot -Tpng splay.dot -o splay.png");
                break;

            case 3:

                cout<<"Cual desea sea el valor buscado?: ";

                cin>>input;

                // root = st.Search(input, root);

                // cout<<"\nDespues de buscar "<<input<<endl;
                // contadorParaVectorNuevo=-1;
                // myfile.open ("splay.dot");
                // myfile2.open ("array.dot");
                // myfile << "digraph { subgraph{ ";
                // st.InOrder(root);
                // myfile << "}}";
                // myfile.close();
                // system("dot -Tpng splay.dot -o splay.png");
                break;

     

            case 4:

                exit(1);

            default:

                cout<<"\n No es opcion! \n";

            }

        }

        cout<<"\n";

        return 0;

    }