#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

#define NUM_ARR_ELEMS(x)  sizeof(x)/sizeof(x[0])


//dado que estos strings serán llamados desde un struct con doble puntero, deben terminar con un valor sentinela "NULL"

const char *es_main_menu_str[] = { "NORMA", "ORIENTACION","FILTRO","HORA","SISTEMA", NULL};
const char *es_submenu_norma_str[] = { "NCh-1","NCh-2","NCh-3","ASME","ESP2", NULL};
const char *es_submenu_orientacion_str[] = { "VERT","HORIZ", NULL};
const char *es_submenu_filtro_str[] = { "FILTRO","NO FILTRO", NULL};
const char *es_submenu_sys_str[] = { "LENGUAJE", "REINICIO","APAGAR", NULL};
const char *es_submenu_hora_str[] = { "ANO","MES", "DIA", "HORA", "MINUTO", NULL};
const char *es_submenu_len_str[] = { "ESPANOL", "INGLES", NULL};

const char *es_dev_tittle = "IS-B";
const char *es_dev_name = "Interruptor Sismico";
const char *es_dev_sw_ver = "SW ver: 1";
const char *es_dev_hw_ver = "HW ver: 1";


const char *en_main_menu_str[] = { "STANDARD", "ORIENTATION","FILTER","DATE","SYSTEM", NULL};
const char *en_submenu_norma_str[] = { "NCh-1","NCh-2","NCh-3","ASME", NULL};
const char *en_submenu_orientacion_str[] = { "VERT","HORIZ", NULL};
const char *en_submenu_filtro_str[] = { "FILTER","NO FILTER", NULL};
const char *en_submenu_sys_str[] = { "LANGUAGE", "REBOOT","SHUTDOWN" , NULL};
const char *en_submenu_hora_str[] = { "YEAR","MONTH", "DAY", "HOUR", "MINUTE", NULL};
const char *en_submenu_len_str[] = { "SPANISH", "ENGLISH" , NULL};

const char *en_dev_tittle = "IS-B";
const char *en_dev_name = "Seismic Switch";
const char *en_dev_sw_ver = "SW ver: 1";
const char *en_dev_hw_ver = "HW ver: 1";

typedef struct lang_ {
    const char **main;
    const char **norma;
    const char **orientacion;
    const char **filtro;
    const char **sys;
    const char **hora;
    const char **leng;
} lang_t;


lang_t es_lang = {  es_main_menu_str, 
                    es_submenu_norma_str, 
                    es_submenu_orientacion_str };

lang_t en_lang = {  en_main_menu_str,
                    en_submenu_norma_str, 
                    en_submenu_orientacion_str};
lang_t *p_lang = NULL;
int main(void) {

    //lang_t *p_lang = NULL;
    p_lang = &en_lang;
    
    for (uint8_t i = 0; p_lang->norma[i] != NULL; ++i) {
        printf("%s\n", p_lang->norma[i]);
    }

    p_lang = &es_lang;
    for (uint8_t i = 0; p_lang->norma[i] != NULL; ++i) {
        printf("%s\n", p_lang->norma[i]);
    }

    return 0;
}
