    /*

     *  C++ Program to Implement Splay Tree

     */

    #include <fstream>

    #include <iostream>

    #include <cstdio>

    #include <cstdlib>

    using namespace std;
    ofstream myfile;
    ofstream myfile2;
    ofstream myfile3;

    int vector[12] = { 5,10,96,30,2,63,85,47,20,3,4,19};
    int vectorArbol[12] = {};
    int contadorParaVectorNuevo = -1;
    struct splay

    {

        int key;

        splay* lchild;

        splay* rchild;

    };

     

    class SplayTree

    {

        public:

            SplayTree()

            {
              splay *der;
              splay *izq;
            }

     

            // RR(Y rotates to the right)

            splay* RR_Rotate(splay* k2)

            {

                splay* k1 = k2->lchild;

                k2->lchild = k1->rchild;

                k1->rchild = k2;

                return k1;

            }

     

            // LL(Y rotates to the left)

            splay* LL_Rotate(splay* k2)

            {

                splay* k1 = k2->rchild;

                k2->rchild = k1->lchild;

                k1->lchild = k2;

                return k1;

            }

     

            // An implementation of top-down splay tree

            splay* Splay(int key, splay* root)

            {

                if (!root)

                    return NULL;

                splay header;

                /* header.rchild points to L tree;

                header.lchild points to R Tree */

                header.lchild = header.rchild = NULL;

                splay* LeftTreeMax = &header;

                splay* RightTreeMin = &header;

                while (1)

                {

                    if (key < root->key)

                    {

                        if (!root->lchild)

                            break;

                        if (key < root->lchild->key)

                        {

                            root = RR_Rotate(root);

                            // only zig-zig mode need to rotate once,

                            if (!root->lchild)

                                break;

                        }

                        /* Link to R Tree */

                        RightTreeMin->lchild = root;

                        RightTreeMin = RightTreeMin->lchild;

                        root = root->lchild;

                        RightTreeMin->lchild = NULL;

                    }

                    else if (key > root->key)

                    {

                        if (!root->rchild)

                            break;

                        if (key > root->rchild->key)

                        {

                            root = LL_Rotate(root);

                            // only zag-zag mode need to rotate once,

                            if (!root->rchild)

                                break;

                        }

                        /* Link to L Tree */

                        LeftTreeMax->rchild = root;

                        LeftTreeMax = LeftTreeMax->rchild;

                        root = root->rchild;

                        LeftTreeMax->rchild = NULL;

                    }

                    else

                        break;

                }

                /* assemble L Tree, Middle Tree and R tree */

                LeftTreeMax->rchild = root->lchild;

                RightTreeMin->lchild = root->rchild;

                root->lchild = header.rchild;

                root->rchild = header.lchild;

                return root;

            }

     

            splay* New_Node(int key)

            {

                splay* p_node = new splay;

                if (!p_node)

                {

                    fprintf(stderr, "Out of memory!\n");

                    exit(1);

                }

                p_node->key = key;

                p_node->lchild = p_node->rchild = NULL;

                return p_node;

            }

     

            splay* Insert(int key, splay* root)

            {

                static splay* p_node = NULL;

                if (!p_node)

                    p_node = New_Node(key);

                else

                    p_node->key = key;

                if (!root)

                {

                    root = p_node;

                    p_node = NULL;

                    return root;

                }

                root = Splay(key, root);

                if (key < root->key)

                {

                    p_node->lchild = root->lchild;

                    p_node->rchild = root;

                    root->lchild = NULL;

                    root = p_node;

                }

                else if (key > root->key)

                {

                    p_node->rchild = root->rchild;

                    p_node->lchild = root;

                    root->rchild = NULL;

                    root = p_node;

                }

                else

                    return root;

                p_node = NULL;

                return root;

            }

     

            splay* Delete(int key, splay* root)

            {

                splay* temp;

                if (!root)

                    return NULL;

                root = Splay(key, root);

                if (key != root->key)

                    return root;

                else

                {

                    if (!root->lchild)

                    {

                        temp = root;

                        root = root->rchild;

                    }

                    else

                    {

                        temp = root;

                        root = Splay(key, root->lchild);

                        root->rchild = temp->rchild;

                    }

                    free(temp);

                    return root;

                }

            }

     

            splay* Search(int key, splay* root)

            {

                return Splay(key, root);

            }

     

            void InOrder(splay* root)

            {

                if (root)

                {

                    InOrder(root->lchild);
                    contadorParaVectorNuevo++;
                    vectorArbol[contadorParaVectorNuevo] = root->key;
                    cout<< "valor: " <<root->key;
                    
                    if(root->lchild){


                        cout<< " | hijo izq: "<< root->lchild->key;
                        myfile << "v"<< root->key;
                        myfile << " -> { ";
                        myfile << "v"<< root->lchild->key;
                        myfile << " }; ";
                    }
                    if(root->rchild){
                        cout << " | hijo der: " << root->rchild->key;
                        myfile << "v"<< root->key;
                        myfile << " -> { ";
                        myfile << "v"<< root->rchild->key;
                        myfile << " }; ";
                         
                    }
                    cout<< "\n";
                    InOrder(root->rchild);

                }
                

            }

    };

     

struct nodoCola{
    splay ptr;
    struct nodoCola *sgte;
};


struct cola{
    struct nodoCola *delante;
    struct nodoCola *atras;
};

void inicializaCola(struct cola &q, splay arbol)
{


    q.delante = NULL;
    q.atras = NULL;
}


void encola(struct cola &q, splay *n)
{
     struct nodoCola *p;
     p = new(struct nodoCola);
     p->ptr = *n;
     p->sgte = NULL;
     if(q.delante==NULL)
         q.delante = p;
     else
         (q.atras)->sgte = p;
     q.atras = p;
}

splay desencola(struct cola &q)
{
    struct nodoCola *p;
    p = q.delante;
    splay n = p->ptr;
    q.delante = (q.delante)->sgte;
    delete(p);
    return n;
}
void recorrerxNivel(splay *arbol)
{
     struct cola q;
     inicializaCola(q,*arbol);
     cout << "\t";
     if(arbol!=NULL)
     {
         encola(q, arbol);

         while(q.delante!=NULL)
         {
             *arbol = desencola(q);
             cout << arbol->key << ' ';
            myfile3 << arbol->key;
            myfile3 << "; ";
            
              myfile3 << arbol->key;
              myfile3  << " -> ";
              
            

             if(arbol->lchild!=NULL)
                 encola(q, arbol->lchild);
             if(arbol->rchild!=NULL)
                 encola(q, arbol->rchild);
         }
     }
     myfile3  << "Fin";
}



    int main()

    {

        SplayTree st;

        


        splay *root;
        root = NULL;

        const int length = 12;

        int i;

        for(i = 0; i < length; i++){
            root = st.Insert(vector[i], root);
        }

        cout<<"\nInOrder: \n";
        contadorParaVectorNuevo=-1;

        st.InOrder(root);

        int input, choice;

        while(1)

        {

                myfile.open ("splay.dot");
                myfile << "digraph { subgraph{ ";
                st.InOrder(root);
                myfile << "}}";
                myfile.close();
                system("dot -Tpng splay.dot -o splay.png");

        cout<<"En el arreglo\n";
            for (int i=0;i<12;i++) {
              cout<<vector[i];
              if((i+1)!=12)
              cout<<",";
            }
              cout<<"\n";
          
          
          // myfile << "Writing this to a file.\n";
          
          cout<<"En el arbol vector\n";
          int limite = (sizeof(vectorArbol)/sizeof(*vectorArbol)) ;
          int indicador = 0;
          myfile2.open ("array.dot");
          myfile2 << "digraph { subgraph{ ";
            for (int i=0;i<limite;i++) {
              if(indicador==vectorArbol[i]){break;}
             
              if(i>0){
                  myfile2 <<"v";
                  myfile2 <<vectorArbol[i-1];
                  myfile2 <<" -> "; 
                  myfile2 <<"v";
                  myfile2 <<vectorArbol[i];
                  myfile2 <<";";
              }
              cout<<vectorArbol[i];
              indicador=vectorArbol[i];
              if((i+1)!=12)
              cout<<",";
            }
            myfile2 << "}}";
            myfile2.close();
           
  
            myfile3.open("arbolEnArray.dot");
            myfile3 << "digraph { subgraph{ ";

            splay *s;
            s->key = root->key;
            s->lchild = root->lchild;
            s->rchild = root->rchild;
            recorrerxNivel(s);
            myfile3 << "}}";
            myfile3.close();
            system("dot -Tpng arbolEnArray.dot -o arbolEnArray.png");
              cout<<"\n";

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

                root = st.Insert(input, root);

                cout<<"\nDespues de inseretar: "<<input<<endl;
                contadorParaVectorNuevo=-1;
                myfile.open ("splay.dot");
                myfile << "digraph { subgraph{ ";
                st.InOrder(root);
                myfile << "}}";
                myfile.close();
                system("dot -Tpng splay.dot -o splay.png");
                break;

            case 2:

                cout<<"Ingrese el valor a eliminar: ";

                cin>>input;

                root = st.Delete(input, root);

                cout<<"\nAfter Delete: "<<input<<endl;
                contadorParaVectorNuevo=-1;
                myfile.open ("splay.dot");
                myfile << "digraph { subgraph{ ";
                st.InOrder(root);
                myfile << "}}";
                myfile.close();
                system("dot -Tpng splay.dot -o splay.png");
                break;

            case 3:

                cout<<"Cual desea sea el valor buscado?: ";

                cin>>input;

                root = st.Search(input, root);

                cout<<"\nDespues de buscar "<<input<<endl;
                contadorParaVectorNuevo=-1;
                myfile.open ("splay.dot");
                myfile << "digraph { subgraph{ ";
                st.InOrder(root);
                myfile << "}}";
                myfile.close();
                system("dot -Tpng splay.dot -o splay.png");
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