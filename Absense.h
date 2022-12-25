#ifndef ABSENSE_H
#define ABSENSE_H
#define CIN_MAX 10 
#include "../utils/date.h"
#include "../employee/Employee.h"
#include <stdio.h>
#include<string.h>

#define DESCRIPTION_TAILLE_MAX 2500

/* Types des absences */

#define ABSENCE_TYPE_MALADIE 1
#define ABSENCE_TYPE_FORMATION 2
#define ABSENCE_TYPE_REUNION 3
#define ABSENCE_TYPE_INJUSITFIEE 4
#define ABSENCE_TYPE_MALADIE_LIBELLEE "maladie"
#define ABSENCE_TYPE_FORMATION_LIBELLEE "formation"
#define ABSENCE_TYPE_REUNION_LIBELLEE "reunion"
#define ABSENCE_TYPE_INJUSITFIEE_LIBELLEE "injustifiee"

#define FILE_NAME_ABSENCE "absence.txt"
#define FILE_NAME_ABSENCEE "absencee.txt"
FILE* fp2;
FILE* fp1;

typedef struct {
  int id_absence;
  int id_employe;
  Date date;
  int type;  // Maladie - Formation - Reunion - injustifiee
  char type_libelle[14];
  int days;
  employe e;
} Absence;


//    %-12d%-16d%-2d\%-2d\%-14d%-14s%-20d     84

char* getAbsenceType2(int type) {
  switch (type) {
    case ABSENCE_TYPE_MALADIE:
      return ABSENCE_TYPE_MALADIE_LIBELLEE;
    case ABSENCE_TYPE_FORMATION:
      return ABSENCE_TYPE_FORMATION_LIBELLEE;
    case ABSENCE_TYPE_REUNION:
      return ABSENCE_TYPE_REUNION_LIBELLEE;
    case ABSENCE_TYPE_INJUSITFIEE:
      return ABSENCE_TYPE_INJUSITFIEE_LIBELLEE;
    default:
      return "Type de conge incorrecte";
  }
}


int getLastIdAbs(){
    fp1=fopen(FILE_NAME_ABSENCE,"r");
    fseek(fp1,-84,SEEK_END);
    int id0,id2;
    fscanf(fp1,"%d%d",&id2,&id0);
    return id0+1;

    fclose(fp1);
}






// ajouter un absence dans le fichier

void ajouteAbs() {
    Absence absence ;
    int tr=0;
    char CIN_emp[CIN_MAX];
    fp2=fopen(FILE_NAME_ABSENCE,"a+");
    if(fp2==NULL){
        printf("fichier n'existe pas\n");
        return ;
    }
    printf("CIN de employe :");
    scanf("%s",CIN_emp);

    if(getIdByCin(CIN_emp)==-1){
        printf("l'employe n'est pas enrigestrer !!!\n");
        

    }else{
        
    absence.id_employe=getIdByCin(CIN_emp);
    printf("le type de absence\n");
    printf("1-->>Absence de maladie \n");
    printf("2-->>Absence de formation\n");
    printf("3-->>Absence de reunion\n");
    printf("4-->>Absence injustifiee \n");
    printf("votre choix:");
    scanf("%d",&absence.type);
    printf("donne nombre des jours d'absence :");
    scanf("%d",&absence.days);
    do{
    printf("date d'absence :");
    printf("jour:");
    scanf("%d",&absence.date.jour);
    printf("mois:");
    scanf("%d",&absence.date.mois);
    printf("annee:");
    scanf("%d",&absence.date.annee);

}while(valideDate(absence.date)==0);


fprintf(fp2,"%-12d%-16d%-2d/%-2d/%-14d%-14s%-20d\n",absence.id_employe,getLastIdAbs(),absence.date.jour,absence.date.mois
                 ,absence.date.annee,getAbsenceType2(absence.type),absence.days);

printf("l'absence a ajouter avec succes\n");
        
    }

    fclose(fp2);
}

//supp un absence 
void suppAbs(){
Absence abs;
int tr=0;
int id_abs;
fp1=fopen(FILE_NAME_ABSENCE,"r");
fp2=fopen(FILE_NAME_ABSENCEE,"w");
printf("id d'absence :");
scanf("%d",&id_abs);

    char buff[84];
    while(fgets(buff,84,fp1)!=NULL){
        sscanf(buff,"%d%d",&abs.id_employe,&abs.id_absence);
        if(id_abs!=abs.id_absence){
            fputs(buff,fp2);
            tr=1;
        }
    }
    if(tr==1){
        printf("l'absence a supprimer avec succes \n");

    }else{
        printf("l'absence n'existe pas !!!\n");
    }

fclose(fp1);fclose(fp2);
remove(FILE_NAME_ABSENCE);
rename(FILE_NAME_ABSENCEE,FILE_NAME_ABSENCE);

}


//recherche un absence  

void rechercheAbs(){
Absence abs;
int tr=0;
int id_abss;
fp2=fopen(FILE_NAME_ABSENCE,"r");
printf("id de absence :");
scanf("%d",&id_abss);
fseek(fp2,84,SEEK_SET);
char buff12[84];
int id11;
while(fgets(buff12,84,fp2)!=NULL){
  sscanf(buff12,"%d%d%d/%d/%d%s%d",&abs.id_employe,&abs.id_absence,
  &abs.date.jour,&abs.date.mois,&abs.date.annee,abs.type_libelle,&abs.days);
  if(id_abss==abs.id_absence){
    printf("[id_employe :%d]  [id_absence : %d]\n",abs.id_employe,abs.id_absence);
    printf("[date d'absence : %d/%d/%d]\n",abs.date.jour,abs.date.mois
    ,abs.date.annee);
    printf("[type d'absence : %s]\n",abs.type_libelle);
    printf("[Nbr de jour d'absence :%d]",abs.days);
    tr=1;
  }
}
if(tr==0){
  printf("l'absence n'existe pas dans BD\n");
  return ;
}




fclose(fp2);
}
/**
 * @brief affche tous les absence de CIN de employe
*/

void AfficheAllAbs(){
Absence abs;
int tr=0;
char CIN_EMP[CIN_MAX];
fp2=fopen(FILE_NAME_ABSENCE,"r");
printf("CIN de employe :");
scanf("%s",CIN_EMP);
fseek(fp2,84,SEEK_SET);
char buff12[84];
int id11;
id11=getIdByCin(CIN_EMP);
while(fgets(buff12,84,fp2)!=NULL){
  sscanf(buff12,"%d%d%d/%d/%d%s%d",&abs.id_employe,&abs.id_absence,
  &abs.date.jour,&abs.date.mois,&abs.date.annee,abs.type_libelle,&abs.days);
  if(abs.id_employe==id11){
    printf("[id_employe :%d]  [id_absence : %d]\n",abs.id_employe,abs.id_absence);
    printf("[nom :%s ]   [prenom :%s]\n",abs.e.nom,abs.e.prenom);
    printf("[date d'absence : %d/%d/%d]\n",abs.date.jour,abs.date.mois
    ,abs.date.annee);
    printf("[type d'absence : %s]\n",abs.type_libelle);
    printf("[Nbr de jour d'absence :%d]",abs.days);
    tr=1;
    printf("\n");
  }
}
if(tr==0){
  printf("l'absence n'existe pas dans BD\n");
  return ;
}

fclose(fp2);

}




#endif