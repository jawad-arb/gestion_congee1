#ifndef DOMANDE_H
#define DOMANDE_H

#include "../utils/date.h"
#include "../employee/Employee.h"
#include <stdio.h>
#include<string.h>

/*code des congee*/
#define CONGE_PAYE 0
#define CONGE_IMPAYE 1
#define CONGE_URGENT 2


#define CIN_MAX 10

/* Libelles des conges */
#define CONGE_PAYE_ITEM   "paye"
#define CONGE_IMPAYE_ITEM "impaye"
#define CONGE_URGENT_ITEM  "urgent"

/* etat de demande */
#define CONGE_ETAT_REFUSE 0
#define CONGE_ETAT_ACCEPTER 1
#define CONGE_ETAT_INDETERMINER 2 //en cas de traitement

/* Libelle d'etat des demandes */
#define DEMANDE_ETAT_REFUSE_ITEM "Refusee"
#define DEMANDE_ETAT_ACCEPTER_ITEM "Acceptee"
#define DEMANDE_ETAT_INDETERMINER_ITEM "Indeterminee"

/*congee par mois*/

#define CONGE_PAR_MOIS 2.5
#define FILE_NAME_DEMANDE "demande.txt"
#define FILE_NAME_DEMANDE_TEMP "temp1.txt"
FILE* fp1;
FILE* file1;

typedef struct {
    int id_demande;
    int id_emp;
    char CIN[CIN_MAX];
    Date dateDeb;
    Date dateFin;
    int etat_demande;
    int conge_code;
    char typeconge[20];
    
}Demande;



char * getDemandeType(int n){
    switch(n){
    case CONGE_PAYE :
        return CONGE_PAYE_ITEM;
    case CONGE_IMPAYE :
        return CONGE_IMPAYE_ITEM;
    case CONGE_URGENT :
        return CONGE_URGENT_ITEM;
    }

}
/**
 * @brief get last id de demande et l'increment
 * @param FILE de demande 
*/

int getLastIdDmd(){
    file1=fopen(FILE_NAME_DEMANDE,"r");
    fseek(file1,-76,SEEK_END);
    int id1,id;
    fscanf(file1,"%d%d",&id,&id1);
    return id1+1;

    fclose(file1);
}

/**
 * @brief ajouter un demande dans un fichier
 * @param id_emp
 * @param id_demande
 * @param dateDeb
 * @param dateFin
 * @param typeCongee
*/



void ajouteDemande(){
    Demande d;
    int id_temp;
    id_temp=getLastIdDmd();
    fp1=fopen(FILE_NAME_DEMANDE,"a");
    printf("CIN :");
    scanf("%s",d.CIN);
    if(getIdByCin(d.CIN)==-1){
        printf("l'employe n'est pas enrigestrer !!!\n");
        

    }else{
        
        d.id_emp=getIdByCin(d.CIN);
        printf("--->>>> entrer le type de congee :\n");
        printf("0--> congee payee\n");
        printf("1--> congee impayee\n");
        printf("2--> congee urgent\n");
        printf("votre choix:");
        scanf("%d",&d.conge_code);
        do{
        printf("la date de debut :\n");
        printf("jour:");
        scanf("%d",&d.dateDeb.jour);
        printf("mois:");
        scanf("%d",&d.dateDeb.mois);
        printf("annee:");
        scanf("%d",&d.dateDeb.annee);
        printf("la date de fin :\n");
        printf("jour:");
        scanf("%d",&d.dateFin.jour);
        printf("mois:");
        scanf("%d",&d.dateFin.mois);
        printf("annee:");
        scanf("%d",&d.dateFin.annee);
        }while(!valideDate(d.dateDeb) && !valideDate(d.dateFin));
        

    fprintf(fp1,"%-12d%-20d%-2d/%-2d/%-10d%-2d/%-2d/%-10d%-10s\n",d.id_emp,id_temp,d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee,d.dateFin.jour,d.dateFin.mois,d.dateFin.annee,getDemandeType(d.conge_code));
        
    }

    fclose(fp1);
}


/**
 * @brief supp un demande en utilisant id de demande
 * @param id_demande
 * 
*/


void suppDemande(){
Demande d;
int tr=0;
int id_dem;
fp1=fopen(FILE_NAME_DEMANDE,"r");
file1=fopen(FILE_NAME_DEMANDE_TEMP,"w");
printf("id de demande :");
scanf("%d",&id_dem);
    char buff[76];
    while(fgets(buff,76,fp1)!=NULL){
        sscanf(buff,"%d%d",&d.id_emp,&d.id_demande);
        if(id_dem!=d.id_demande){
            fputs(buff,file1);
            tr=1;
        }
    }
    if(tr==1){
        printf("demande a supprimer avec succes \n");

    }else{

        printf("demande n'existe pas !!!\n");
    }

fclose(fp1);fclose(file1);
remove(FILE_NAME_DEMANDE);
rename(FILE_NAME_DEMANDE_TEMP,FILE_NAME_DEMANDE);

}


// afficher un demande  

void RechercheDemande(){
    Demande d;
    int tr=0;
    int idd;
    file1=fopen(FILE_NAME_DEMANDE,"r");

    printf("id de demande :");
    scanf("%d",&idd);
    fseek(file1,76,SEEK_SET);
    char buff1[76];
    while(fgets(buff1,76,file1)!=NULL){
        sscanf(buff1,"%d%d%d/%d/%d%d/%d/%d%s",&d.id_emp,&d.id_demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee
        ,d.typeconge);
        if(d.id_demande==idd){
            printf("[id_employe :%d ]\n",d.id_emp);
            printf("[id_demande :%d]\n",d.id_demande);
            printf("[date de debut :%d-%d-%d]\n",d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee);
            printf("[date de fin :%d-%d-%d]\n",d.dateFin.jour
        ,d.dateFin.mois,d.dateFin.annee);
            printf("[type de congee :%s]\n",d.typeconge);
            printf("[solde de congee :%d]\n",getDiffDays(d.dateFin,d.dateDeb));
        tr=1;
        }

    }
    if(tr==0){
            printf("demande n'existe pas\n");
        
    }
    
    fclose(file1);
}

/**
 * @brief affiche toute les demandes de employe .
 * @param entrer CIN apres id de employe 
 * @return  les demandes des cette employe 
*/

void afficheAllDemande(){
    Demande d;
    int tr=0;
    int id_eemp;
    char CIN[CIN_MAX];
    file1=fopen(FILE_NAME_DEMANDE,"r");

    printf("CIN de demande :");
    scanf("%s",CIN);
    id_eemp=getIdByCin(CIN);
    fseek(file1,76,SEEK_SET);
    char buff1[76];
    while(fgets(buff1,76,file1)!=NULL){
        sscanf(buff1,"%d%d%d/%d/%d%d/%d/%d%s",&d.id_emp,&d.id_demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee
        ,d.typeconge);
        if(d.id_emp==id_eemp){
            printf("[id_employe :%d ]\n",d.id_emp);
            printf("[id_demande :%d]\n",d.id_demande);
            printf("[date de debut :%d-%d-%d]\n",d.dateDeb.jour
        ,d.dateDeb.mois,d.dateDeb.annee);
        printf("[date de fin :%d-%d-%d]\n",d.dateFin.jour
        ,d.dateFin.mois,d.dateFin.annee);
        printf("[type de congee :%s]\n",d.typeconge);
        printf("[solde de congee :%d]",getDiffDays(d.dateFin,d.dateDeb));
        printf("------------**********--------------\n");
        tr=1;
        }

    }
    if(tr==0){
            printf("demande n'existe pas\n");
        
    }
    
    fclose(file1);



}






//nombre des demande payee
int NbrDemandePayee(){
    Demande d;
    int n=0;
    file1=fopen(FILE_NAME_DEMANDE,"r");
    fseek(file1,76,SEEK_SET);
    char buff2[76];
    while(fgets(buff2,76,file1)!=NULL){
        sscanf(buff2,"%d%d%d/%d/%d%d/%d/%d%s",&d.id_emp,&d.id_demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee
        ,d.typeconge);
        if(strcmp(d.typeconge,"paye")==0){
                n++;
        }
        
    }
    return n;

    fclose(file1);
  
}


// nombre des demande urgent

int NbrDemandeUrgent(){
    Demande d;
    int m=0;
    file1=fopen(FILE_NAME_DEMANDE,"r");
    fseek(file1,76,SEEK_SET);
    char buff3[76];
    while(fgets(buff3,76,file1)!=NULL){
        sscanf(buff3,"%d%d%d/%d/%d%d/%d/%d%s",&d.id_emp,&d.id_demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee
        ,d.typeconge);
        if(strcmp(d.typeconge,"urgent")==0){
                m++;
        }
        
    }
    return m;

    fclose(file1);
  
}

// nombre des demande impayee
int NbrDemandeImPayee(){
Demande d;
    int l=0;
    file1=fopen(FILE_NAME_DEMANDE,"r");
    fseek(file1,76,SEEK_SET);
    char buff4[76];
    while(fgets(buff4,76,file1)!=NULL){
        sscanf(buff4,"%d%d%d/%d/%d%d/%d/%d%s",&d.id_emp,&d.id_demande,&d.dateDeb.jour
        ,&d.dateDeb.mois,&d.dateDeb.annee,&d.dateFin.jour,&d.dateFin.mois,&d.dateFin.annee
        ,d.typeconge);
        if(strcmp(d.typeconge,"impaye")==0){
                l++;
        }
        
    }
    return l;

    fclose(file1);


}






#endif
