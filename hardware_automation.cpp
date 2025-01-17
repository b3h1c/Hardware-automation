#include <iostream>
#include <fstream>
#include <string.h>
#include <conio.h>
#include <math.h>

using namespace std;


struct Malzeme{
	char ad[80];
	char marka[80];
	char kod[5];
	int adet;	
};
Malzeme mlz;
void MlzEkleme();
void MlzSilme();
void MlzListeleme();
void MlzGuncelleme();
void MlzArama();
int main(){
	setlocale(LC_ALL,"Turkish");
	
	char menu;
	
	do{
	system("cls");
	
	char secim;
	cout<<"|----------Hoþgeldiniz----------|"<<endl;
	cout<<"|       1)Malzeme Ekleme        |"<<endl;
	cout<<"|       2)Malzeme Silme         |"<<endl;
	cout<<"|      3)Malzeme Listeleme      |"<<endl;
	cout<<"|      4)Malzeme Güncelleme     |"<<endl;
	cout<<"|       5)Malzeme Arama         |"<<endl;
	cout<<"|-------------------------------|"<<endl;
	
	cout<<"Bir islem secin: ";
	cin>>secim;
	switch (secim){
		case '1':
		 MlzEkleme();
			break;

		case '2':
		  MlzSilme();
			break;

		case '3': 
		
	      MlzListeleme();	
			break;
		
		case '4': 
		
		    MlzGuncelleme();
			break;
		
		case '5': 
		
	      MlzArama();
			break;
		
		default:
		cout<<"Hatalý Giris Yapildi.."<<endl; 						
	}
	cout<<"Anamenuye donmek icin a cýkmak icin c ye basýn.";
	menu=getche();
	
   }while(menu=='a');
	
	
	
	system ("pause");
	return 0;
}

void MlzEkleme(){
	ofstream yaz("Hardware_Automation.dat",ios::binary | ios::app);
	int adet=0;
	char secim;
	
	do{
	cout<<"Malzeme adýný giriniz: ";
	cin>>mlz.ad;
	cout<<"Malzeme markasini giriniz: ";
	cin>>mlz.marka;
	cout<<"Malzeme kodunu giriniz: ";
	cin>>mlz.kod;
	cout<<"Malzeme adedini giriniz: ";
	cin>>mlz.adet;
	yaz.write((char*)&mlz ,sizeof(mlz));
	adet++;
	cout<<endl;
	cout<<"Baþka kayit yapicak misin?(e/h) ";
	secim=getche();
	cout<<endl;
		
	}while(secim=='e'||secim=='E');
	
	cout<<adet<<" adet malzeme eklendi."<<endl;
	yaz.close();
}

void MlzListeleme(){
	ifstream oku("Hardware_Automation.dat",ios::binary|ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mlz);
	cout<<"Toplam kayit adedi: "<<kayits<<endl;
	
	if(kayits>0){
		for(int i=0;i<kayits;i++){
			oku.seekg(i*sizeof(mlz));
			oku.read((char*)&mlz,sizeof(mlz));
			cout<<endl;
			cout<<"**"<<i+1<<". Malzemenin Bilgileri **"<<endl;
			cout<<"Malzemenin adý: "<<mlz.ad<<endl;
			cout<<"Malzemenin markasý: "<<mlz.marka<<endl;
			cout<<"Malzemenin kodu: "<<mlz.kod<<endl;
			cout<<"Malzemenin adedi: "<<mlz.adet<<endl;
		}
	
	}
	else {
		cout<<"Kayit Bulunamadi...."<<endl;
	}
	oku.close();
}

void MlzArama(){
	
	ifstream oku("Hardware_Automation.dat",ios::binary|ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mlz);
     
     char kod[100];
	 cout<<"Aramak istediginiz malzemenin kodunu girin: ";
     cin>>kod;
	
	if(kayits>0){
		for(int i=0;i<kayits;i++){
			oku.seekg(i*sizeof(mlz));
			oku.read((char*)&mlz,sizeof(mlz));
		   
		   if(strcmp(mlz.kod,kod)==0){
	
			cout<<"** Malzemenin Bilgileri **"<<endl;
			cout<<"Malzemenin adý: "<<mlz.ad<<endl;
			cout<<"Malzemenin markasý: "<<mlz.marka<<endl;
			cout<<"Malzemenin kodu: "<<mlz.kod<<endl;
			cout<<"Malzemenin adedi: "<<mlz.adet<<endl;
          }
         
		}
	
	}
     	else 
		cout<<"Kayit Bulunamadi...."<<endl;
	
	oku.close();
	
}

void MlzSilme(){
	
	ifstream oku("Hardware_Automation.dat",ios::binary|ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mlz);
     
     bool sil=false;
     char kod[100];
	 cout<<"Silmek istediginiz malzemenin kodunu girin: ";
     cin>>kod;
     char secim;
	
		for(int i=0;i<kayits;i++){
			oku.seekg(i*sizeof(mlz));
			oku.read((char*)&mlz,sizeof(mlz));
		   
		   if(strcmp(mlz.kod,kod)==0){
	
			cout<<"** Malzemenin Bilgileri **"<<endl;
			cout<<"Malzemenin adý: "<<mlz.ad<<endl;
			cout<<"Malzemenin markasý: "<<mlz.marka<<endl;
			cout<<"Malzemenin kodu: "<<mlz.kod<<endl;
			cout<<"Malzemenin adedi: "<<mlz.adet<<endl;
			
			cout<<"Silmek istediginiz malzeme bu mu? (e/h)";
			secim=getche();
			
			if(secim=='h'||secim=='H'){
				Malzeme y_mlz;
				ofstream yeni("y_file.dat",ios::binary|ios::app);
			     strcpy(y_mlz.ad,mlz.ad);
			     strcpy(y_mlz.kod,mlz.kod);
			     strcpy(y_mlz.marka,mlz.marka);
			     y_mlz.adet=mlz.adet;
				
				yeni.write((char*)&mlz,sizeof(mlz));
				yeni.close();
			}
			else if(secim=='e'||secim=='E'){
				sil=true;
			}
          }
          else {
          	    Malzeme y_mlz;
				ofstream yeni("y_file.dat",ios::binary|ios::app);
			     strcpy(y_mlz.ad,mlz.ad);
			     strcpy(y_mlz.kod,mlz.kod);
			     strcpy(y_mlz.marka,mlz.marka);
			     y_mlz.adet=mlz.adet;
				
				yeni.write((char*)&mlz,sizeof(mlz));
				yeni.close();
			}
		  }
         oku.close();

		if(sil){
			remove("Hardware_Automation.dat");
			rename("y_file.dat","Hardware_Automation.dat");
			cout<<"\n Kayit Silindi.."<<endl;
		}
		else {
			remove("y_file.dat");
			cout<<"\n Kayit Bulunamadi.."<<endl;
		}

}

void MlzGuncelleme(){
	
	ifstream oku("Hardware_Automation.dat",ios::binary|ios::app);
	
	oku.seekg(0,ios::end);
	int kayits=oku.tellg()/sizeof(mlz);
     
     bool degis=false;
     char kod[100];
	 cout<<"Kaydýný düzeltmek istediginiz malzemenin kodunu girin: ";
     cin>>kod;
     char secim;
	
		for(int i=0;i<kayits;i++){
			oku.seekg(i*sizeof(mlz));
			oku.read((char*)&mlz,sizeof(mlz));
		   
		   if(strcmp(mlz.kod,kod)==0){
	
			cout<<"** Malzemenin Bilgileri **"<<endl;
			cout<<"Malzemenin adý: "<<mlz.ad<<endl;
			cout<<"Malzemenin markasý: "<<mlz.marka<<endl;
			cout<<"Malzemenin kodu: "<<mlz.kod<<endl;
			cout<<"Malzemenin adedi: "<<mlz.adet<<endl;
			
			cout<<"Silmek istediginiz malzeme bu mu? (e/h)";
			secim=getche();
			
			if(secim=='e'||secim=='E'){
				degis=true;
                        ofstream guncelle("y_file.dat",ios::app|ios::binary);
                        cout<<endl;
						cout << "Malzeme adýný giriniz: ";
						cin>> mlz.ad;
						cout << "Malzeme markasý giriniz: ";
						cin>> mlz.marka;
						cout << "Malzeme kodu giriniz: " ;
						cin>>mlz.kod;
						cout << "Malzeme adedi giriniz: ";
			            cin>>mlz.adet;
						cout << endl;
		  
                        guncelle.write((char*)&mlz, sizeof(mlz));
                        guncelle.close();
				
			}
			
          }
          else {
          	    Malzeme y_mlz;
				ofstream yeni("y_file.dat",ios::binary|ios::app);
			     strcpy(y_mlz.ad,mlz.ad);
			     strcpy(y_mlz.kod,mlz.kod);
			     strcpy(y_mlz.marka,mlz.marka);
			     y_mlz.adet=mlz.adet;
				
				yeni.write((char*)&mlz,sizeof(mlz));
				yeni.close();
			}
		  }
         oku.close();

		if(degis){
			remove("Hardware_Automation.dat");
			rename("y_file.dat","Hardware_Automation.dat");
			cout<<"\n Kayit Duzeltildi.."<<endl;
		}
		else {
			remove("y_file.dat");
			cout<<"\n Kayit Bulunamadi.."<<endl;
		}

}
