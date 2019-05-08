#include <iostream>

using namespace std;

class Matrice {
    int **a;
    int lin, col;
public:
    Matrice();
    ~Matrice();
    Matrice(Matrice &);
    void setLin(int i){lin=i;}
    void setCol(int i){col=i;}
    int getLin(){return lin;}
    int getCol(){return col;}
    int** getMat(){return a;}
    int getVal(int i, int j){return a[i][j];}
    void alocareSpatiu(int linii, int coloane);
    void adaugareVecinatate(int x, int y);
    int verificareVecinatate(int x, int y);
    void operator=(const Matrice &ob);
    friend istream& operator>>(istream& in, Matrice &ob);
    friend ostream& operator<<(ostream& out, Matrice &ob);
};

Matrice::Matrice(){
    a=NULL;
}

Matrice::~Matrice(){
    if (a!=NULL){
        for (int i=0; i<lin; i++){
            delete[] (a[i]);
        }
        delete[] a;
    }
    col=0;
    lin=0;
}

Matrice::Matrice(Matrice &ob){
    int l=ob.lin;
    int c=ob.col;
    this->alocareSpatiu(l,c);
    this->lin=l;
    this->col=c;

    for(int i=0; i<l; i++){
        for (int j=0; j<c; j++){
            a[i][j]=ob.a[i][j];
        }
    }

}

void Matrice::operator=(const Matrice &ob){
    int l=ob.lin;
    int c=ob.col;
    if (a!=NULL){
        for (int i=0; i<lin; i++){
            delete[] (a[i]);
        }
        delete[] a;
    }
    this->alocareSpatiu(l,c);
    this->lin=l;
    this->col=c;
    for(int i=0; i<l; i++){
        for (int j=0; j<c; j++){
            a[i][j]=ob.a[i][j];
        }
    }
}

void Matrice::alocareSpatiu(int linii, int coloane){
    a=new int*[linii];
    for (int i=0; i<linii; i++){
        a[i]=new int[coloane];
    }
}

void Matrice::adaugareVecinatate(int x, int y){
    a[x][y]=1;
}

int Matrice::verificareVecinatate(int x, int y){
    if (a[x][y]==1){
        return 1;
    }
    return 0;
}

istream& operator>>(istream& in, Matrice &ob){
    cout<<"Introduceti numarul de linii: ";
    in>>ob.lin;
    cout<<"Introduceti numarul de coloane: ";
    in>>ob.col;

    ob.alocareSpatiu(ob.lin,ob.col);

    int nr,l,c;

    for (int i=0; i<ob.lin; i++){
        for (int j=0; j<ob.col; j++){
            in>>ob.a[i][j];
        }
    }
    return in;
}

ostream& operator<<(ostream& out, Matrice &ob){
    out<<'\n';
    for (int i=0; i<ob.lin; i++){
        for (int j=0; j<ob.col; j++){
            out<<ob.a[i][j]<<' ';
        }
        out<<'\n';
    }
    return out;
}

class Vector {
    int *v;
    int dim;
public:
    Vector();
    ~Vector();
    Vector(Vector &ob);
    void setDim(int i){dim=i;}
    int getDim(){return dim;}
    void operator=(const Vector &ob);
    friend istream &operator>>(istream &in, Vector &ob);
    friend ostream &operator<<(ostream &out, Vector &ob);
};

Vector::Vector(){
    v=NULL;
    dim=0;
}

Vector::~Vector(){
    delete[] v;
    dim=0;
}

Vector::Vector(Vector &ob){
    dim=ob.dim;
    v=new int [dim];
    for (int i=0; i<dim; i++){
        v[i]=ob.v[i];
    }
}

void Vector::operator=(const Vector& ob){
    dim=ob.dim;
    delete []v;
    v=new int [dim];
    for (int i=0; i<dim; i++){
        v[i]=ob.v[i];
    }
}

istream& operator>>(istream& in, Vector& ob){
    cout<<"Introduceti dimensiunea vectorului: ";
    in>>ob.dim;
    ob.v=new int[ob.dim];
    cout<<"Introduceti cele "<<ob.dim<<" elemente:";
    for (int i=0; i<ob.dim; i++){
        in>>ob.v[i];
    }
    return in;
}

ostream& operator<<(ostream &out, Vector &ob){
    for (int i=0; i<ob.dim; i++){
        out<<ob.v[i]<<' ';
    }
    return out;
}

class Lista{
    Vector *l;
    int nrVect;
public:
    Lista();
    ~Lista();
    Lista(Lista &ob);
    void setNrVect(int i){nrVect=i;}
    int getNrVect(){return nrVect;}
    Vector* getVect () {return l;}
    void operator= (const Lista &ob);
    friend istream &operator>>(istream &in, Lista &ob);
    friend ostream &operator<<(ostream &out, Lista &ob);
};

Lista::Lista(){
    nrVect=0;
    l=NULL;
}

void Lista::operator=(const Lista &ob){
    nrVect=ob.nrVect;
    delete[] l;
    l=new Vector[nrVect];
    for (int i=0; i<nrVect; i++){
        l[i]=ob.l[i];
    }
}

Lista::~Lista(){
    nrVect=0;
    delete []l;
}

Lista::Lista(Lista &ob){
    nrVect=ob.nrVect;
    l=new Vector [nrVect];
    for (int i=0; i<nrVect; i++){
        l[i]=ob.l[i];
    }
}

istream &operator>>(istream &in, Lista &ob){
    cout<<"Introduceti numarul de vectori: ";
    in>>ob.nrVect;
    ob.l=new Vector[ob.nrVect];
    for (int i=0; i<ob.nrVect; i++){
        in>>ob.l[i];
    }
    return in;
}

ostream &operator<<(ostream &out, Lista &ob){
    for (int i=0; i<ob.nrVect; i++){
        out<<ob.l[i];
        out<<'\n';
    }
    return out;
}

class Graf {
    int nrNoduri;
public:
    Graf();
    ~Graf();
    virtual void setNrNoduri(int i){nrNoduri=i;}
    virtual int getNrNoduri(){return nrNoduri;}
    virtual int verificareConexitate(int nod)=0;
};

Graf::Graf(){
    nrNoduri=0;
}

Graf::~Graf(){
    nrNoduri=0;
}

class Graf_Neorientat:protected Graf{
    Lista l;
public:
    Graf_Neorientat();
    Graf_Neorientat(Graf_Neorientat &ob);
    ~Graf_Neorientat();
    int verificareConexitate(int nod){cout<<"Graful nu este orientat\n";return 0;}
    void operator= (const Graf_Neorientat &ob);
    friend istream& operator>>(istream &in, Graf_Neorientat& ob);
    friend ostream &operator<<(ostream &out, Graf_Neorientat &ob);
};

void Graf_Neorientat::operator= (const Graf_Neorientat &ob){
    l=ob.l;
}

Graf_Neorientat::Graf_Neorientat(){
    l.setNrVect(0);
}

Graf_Neorientat::Graf_Neorientat(Graf_Neorientat &ob){
    l=ob.l;
}

Graf_Neorientat::~Graf_Neorientat(){
    l.setNrVect(0);
}

istream &operator>>(istream &in, Graf_Neorientat &ob){
    int x;
    cout<<"Introduceti numarul de noduri: ";
    in>>x;
    ob.setNrNoduri(x);
    in>>ob.l;
    return in;
}

ostream &operator<<(ostream &out, Graf_Neorientat &ob){
    out<<ob.l;
    return out;
}

class Graf_Orientat:protected Graf{
    Matrice m;
public:
    Graf_Orientat();
    ~Graf_Orientat();
    Graf_Orientat(Graf_Orientat &);
    int verificareConexitate(int nod);
    void operator= (const Graf_Orientat &ob);
    friend istream& operator>>(istream &in, Graf_Orientat &ob);
    friend ostream &operator<<(ostream &out, Graf_Orientat &ob);
};

void Graf_Orientat::operator= (const Graf_Orientat &ob){
    m=ob.m;
}

Graf_Orientat::Graf_Orientat(){
    m.setLin(0);
    m.setCol(0);
}

Graf_Orientat::Graf_Orientat(Graf_Orientat &ob){
    m=ob.m;
}

Graf_Orientat::~Graf_Orientat(){
    m.setLin(0);
    m.setCol(0);
}

istream &operator>>(istream &in, Graf_Orientat &ob){
    int x;
    cout<<"Introduceti numarul de noduri: ";
    in>>x;
    ob.setNrNoduri(x);
    in>>ob.m;
    return in;
}

ostream &operator<<(ostream &out, Graf_Orientat &ob){
    out<<ob.m;
    return out;
}

int Graf_Orientat::verificareConexitate(int nod){
    int lun=getNrNoduri();
    int noduriVizitate=1;
    int *coada, *viz;
    coada=new int[lun+3];
    viz=new int[lun+3];
    int first=1;
    int last=1;
    coada[first]=nod;
    viz[nod]=1;
    int rasp=0;
    while (first<=last){
        /// parcurgem linia
        for (int i=0; i<lun; i++){
            if (m.getVal(coada[first],i)==1 && viz[i]!=1){
                last++;
                coada[last]=i;
                viz[i]=1;
                noduriVizitate++;
            }
        }
        /// parcurgem coloana
        for (int i=0; i<lun; i++){
            if (m.getVal(i,coada[first])==1 && viz[i]!=1){
                last++;
                coada[last]=i;
                viz[i]=1;
                noduriVizitate++;
            }
        }

        if (noduriVizitate==lun){
            rasp=1;
            break;
        }
        first++;
    }
    if (rasp==0){
        cout<<"Graful nu este conex.\n";
    }
    else{
        int *coada1, *viz1;
        coada1=new int[lun+3];
        viz1=new int[lun+3];
        first=1;
        last=1;
        coada1[first]=nod;
        viz1[nod]=1;
        while (first<=last){
            /// parcurgem coloana
            for (int i=0; i<lun; i++){
                if (m.getVal(i,coada1[first])==1 && viz1[i]!=1){
                    last++;
                    coada1[last]=i;
                    viz1[i]=1;
                }
            }
            first++;
        }
        cout<<"Vectorul de tati: ";
        for (int i=2; i<=last; i++){
            cout<<coada1[i]<<' ';
        }
        cout<<"\n";
    }
    return 0;
}

int main () {
    /// MENIU
    int continuare=1;
    while (continuare){
        cout<<"Introduceti tipul grafului ce va fi citit:\n1.Neorientat\n2.Orientat\n3.Exit\n";
        int key;
        cin>>key;
        if (key==1){
            Graf_Neorientat a;
            cin>>a;
            int key2;
            cout<<"Operatii:\n1.Declararea unui alt graf b urmata de b=a si afisarea lui b\n2.Testare conexitate pentru un nod introdus\n";
            cin>>key2;
            if (key2==1){
                Graf_Neorientat b;
                b=a;
                cout<<b;
            }
            if (key2==2){
                int nod;
                cout<<"Introduceti nodul: ";
                cin>>nod;
                a.verificareConexitate(nod);
            }
        }
        if (key==2){
            Graf_Orientat a;
            cin>>a;
            int key2;
            cout<<"Operatii:\n1.Declararea unui alt graf b urmata de b=a si afisarea lui b\n2.Testare conexitate si afisare vector de tati pentru un nod introdus\n";
            cin>>key2;
            if (key2==1){
                Graf_Orientat b;
                b=a;
                cout<<b;
            }
            if (key2==2){
                int nod;
                cout<<"Introduceti nodul: ";
                cin>>nod;
                a.verificareConexitate(nod);
            }
        }
        if (key==3){
            continuare=0;
        }
    }

    return 0;
}
