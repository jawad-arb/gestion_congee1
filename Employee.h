#ifndef EMPLOYEE_H
#define EMPLOYEE_H


#include "../utils/date.h"
#include <stdio.h>
#include<string.h>

#define CIN_MAX 10
#define NOM_MAX 20
#define PRENOM_MAX 20
#define NUM_TELE_MAX 10
#define FILE_NAME "employe.txt"
#define FILE_NAME_TEMP "temp.txt"
FILE* fp;
FILE* file;

typedef struct employe {
    int id ;
    char CIN[CIN_MAX];
    char nom[NOM_MAX];
    char prenom[PRENOM_MAX];
    char Num_tele_emp[NUM_TELE_MAX];
    Date date_naiss;
    float salaire;
}employe;



//  get the last id of employe 

int getLastEmpId(){
    FILE* fp;
    fp=fopen(FILE_NAME,"r");
    fseek(fp,-99,SEEK_END);
    int id;
    fscanf(fp,"%d",&id);
    return id+1;

    fclose(fp);
}

//   ajout un employe dans un fichier 

void ajoutEmp(){
    fp=fopen(FILE_NAME,"at+");
    employe e;
    int tr=0;
    char CIN_temp[CIN_MAX];
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",&CIN_temp);
    printf("\n-----------*********------------\n");
    
    char buff1[99],cin[CIN_MAX];
    int id ;
    
    fseek(fp,99,SEEK_SET);
        while(fgets(buff1,99,fp)!=NULL){
        sscanf(buff1,"%d%s",&id,cin);

        if(strcmp(cin,CIN_temp)==0){
            printf("employe existe .\n");
            tr=1;
            break;
        }
    }
    if(tr==0){

    printf("\n-----------*********------------\n");
    printf("\n-----------*********------------\n");
    printf("nom:");
    scanf("%s",e.nom);
    printf("prenom:");
    scanf("%s",e.prenom);
    printf("numero de telephone :");
    scanf("%s",e.Num_tele_emp);
    do{
    printf("date naissance :");
    printf("jour:");
    scanf("%d",&e.date_naiss.jour);
    printf("mois:");
    scanf("%d",&e.date_naiss.mois);
    printf("annee:");
    scanf("%d",&e.date_naiss.annee);
    printf("salaire:");
    scanf("%f",&e.salaire);

    }while(valideDate(e.date_naiss)==0);

    fprintf(fp,"%-10d%-10s%-15s%-15s%-15s%d/%d/%-14d%-12.2f\n",getLastEmpId(),CIN_temp,e.nom,e.prenom,e.Num_tele_emp,
            e.date_naiss.jour,e.date_naiss.mois,e.date_naiss.annee, e.salaire);
            printf("\n-----------*********------------\n");

            printf("\n\n l'employe a enregistrer avec succes \n");
            printf("\n-----------*********------------\n");
        }

    fclose(fp);


    }

    //supp un employe 

    
void suppEmp(){
employe e;
char CIN_temp[10];
fp=fopen(FILE_NAME,"r");
file=fopen(FILE_NAME_TEMP,"w");
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",&CIN_temp);
    printf("\n-----------*********------------\n");


    char buff[99], cin[10];
    int id;
    int found = 0;
   
    while(fgets(buff,99,fp)!=NULL){
        sscanf(buff,"%d%s",&id,cin);
        

        if(strcmp(CIN_temp,cin)!=0) {
            fputs(buff,file);
            found=1;
        } 
    }

    if(found==1) {
        printf("\n-----------*********------------\n");
        printf("    l'employe a supprimer avec succes \n");
        printf("\n-----------*********------------\n");

        
    }else {
        printf("    cin non trouvable \n");
    }
        fclose(fp);fclose(file);
        remove(FILE_NAME);
        rename(FILE_NAME_TEMP,FILE_NAME);

}


void rechercheEmp(){
    employe e;

    fp=fopen(FILE_NAME,"r");
    char cin[20];
    printf("\n-----------*********------------\n");
    printf("    CIN:");
    scanf("%s",&cin);
    printf("\n-----------*********------------\n");
    char buff[99], fCin[20];
    int id;

    fseek(fp,99,SEEK_CUR);
    while(fgets(buff,99,fp)!=NULL){
        sscanf(buff,"%d%s%s%s%s%d/%d/%d%f",&id,fCin,e.nom,e.prenom,e.Num_tele_emp
        ,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee,&e.salaire);
        if(strcmp(cin,fCin)==0) {
            printf("[id:%d  CIN : %s]  [nom : %s   prenom : %s   ]\n",id,fCin,e.nom,e.prenom);
            printf("[date naissance:%d/%d/%d]  [salaire : %f  ]\n",e.date_naiss.jour
            ,e.date_naiss.mois,e.date_naiss.annee,e.salaire);
            return;
        }
    }

    printf("cin non trouvable \n");



    fclose(fp);

    }


void afficheToutEmp(){
    employe e;
    fp=fopen(FILE_NAME,"r");
    char cin[20];
    printf(" ---- affichege de toute les employes  ----  ");
    printf("\n--------------*********------------\n");
    
    

    char buff[99];
    int id;

    fseek(fp,99,SEEK_SET);
    while(fgets(buff,99,fp)!=NULL){
        sscanf(buff,"%d%s%s%s%s%d/%d/%d%f",&id,e.CIN,e.nom,e.prenom,e.Num_tele_emp
        ,&e.date_naiss.jour,&e.date_naiss.mois,&e.date_naiss.annee,&e.salaire);

        printf("[id:%d  CIN : %s]  [nom : %s   prenom : %s   ]\n",id,e.CIN,e.nom,e.prenom);
        printf("[date naissance:%d/%d/%d]  [salaire : %.2f  ]\n",e.date_naiss.jour
            ,e.date_naiss.mois,e.date_naiss.annee,e.salaire);
            printf("\n-----------*********------------\n");
            
    }
    fclose(fp);

    }
    
int getIdByCin(char* cin){
fp=fopen(FILE_NAME,"r");

char buff[99], fCin[20];
    int id;
    fseek(fp,99,SEEK_CUR);
    while(!feof(fp)) {
        fgets(buff,99, fp);
        sscanf(buff,"%d%s",&id,fCin);
        if(strcmp(cin,fCin)==0) {

            return id ;
        }
    }
    return -1;
fclose(fp);

}

/**
 * @brief Obtenir le nombre des employes
 * 
 * @return int 
 */

int NbrOfEmploye(){
    int n;
    fp=fopen(FILE_NAME,"r");
    char buff11[99];
    fseek(fp,99,SEEK_SET);
    while(fgets(buff11,99,fp)!=NULL){
        n++;

    }
    return n;

    fclose(fp);
}

/**
 * @brief donner le nom est prenom d'apres CIN
 * @param CIN char 
*/


















#endif