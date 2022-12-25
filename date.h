#include<time.h>
#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED

#define SEC_PER_MIN 60
#define MIN_PER_HOUR 60
#define HOUR_PER_DAY 24




/*********************** date *********************/

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;

//verifier si deux date sont equal

int isEqualDate(Date d1 , Date d2){

    return (d1.annee==d2.annee && d1.mois==d2.mois && d1.jour==d2.jour) ;
}
//verifier si la date est correct

int valideDate(Date date){
    return (date.jour>0 && date.jour<=31)
        &&(date.mois>0 && date.mois<=12)
        &&(date.annee>1960);
}

//verifier si la date 1 est inferieur a la date 2 :

int isGreaterThan(Date d1 , Date d2){
    if(!valideDate(d1) || !valideDate(d2));
        return 0;
    return d1.annee<d2.annee ||(d1.annee==d2.annee && (d1.mois <d2.mois || (d1.mois==d2.annee && d1.jour < d2.jour)));
}

/**
 * @brief Calculer le nombre de jours entre la date 1 et la date 2 (Date1 - Date2)
 *
 * @param d1 Date 1
 * @param d2 Date 2
 * @return int
 */
int getDiffDays(Date d1, Date d2) {
  if (isEqualDate(d1, d2))
    return 0;

  struct tm t1;
  t1.tm_isdst = -1;
  t1.tm_sec    = 0;
  t1.tm_min    = 0;
  t1.tm_hour   = 0;
  t1.tm_mday   = d1.jour;
  t1.tm_mon    = d1.mois - 1;
  t1.tm_year   = d1.annee - 1900;

  struct tm t2;
  t2.tm_isdst = -1;
  t2.tm_sec    = 0;
  t2.tm_min    = 0;
  t2.tm_hour   = 0;
  t2.tm_mday   = d2.jour;
  t2.tm_mon    = d2.mois - 1;
  t2.tm_year   = d2.annee - 1900;

  return difftime(mktime(&t1), mktime(&t2)) / (int) (SEC_PER_MIN * MIN_PER_HOUR * HOUR_PER_DAY);
}


#endif // DATE_H_INCLUDED
