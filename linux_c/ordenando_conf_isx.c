#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdbool.h"


typedef float  float32_t;

static const uint8_t ch1_horiz[] = {0,0,1};
static const uint8_t ch1_vert[] = {1,0,0};
static const uint8_t ch2_horiz[] = {1,1,0};
static const uint8_t ch2_vert[] = {0,1,1};
static const uint8_t ch3_horiz[] = {1,1,0};
static const uint8_t ch3_vert[] = {0,1,1};
static const uint8_t asme_h[] = {0,0,1};
static const uint8_t asme_v[] = {1,0,0};

static const float32_t ch1_thrhld = 150.0f;
static const float32_t ch2_thrhld = 200.0f;
static const float32_t ch3_thrhld = 500.0f;
static const float32_t esp_thrhld = 150.0f;

typedef struct
{
	uint16_t fs;
	uint16_t chunk_size;
	uint8_t trigger_votes;
	float32_t threshold;
	uint8_t axis_votes[3];
	uint8_t filter_en;

} mVt_filt_detect_Parameter_t;


typedef enum
{
	CH1_CFG = 0,
	CH2_CFG,
	CH3_CFG,
	ESP1_CFG,
	ESP2_CFG
}standardConfigType;

typedef enum
{
	VERTICAL_CFG = 0,
	HORIZONTAL_CFG,
}orientConfigType;

typedef enum
{
	SUB_MENU_FILTER_CFG = 0,
	SUB_MENU_NO_FILTER_CFG
}filterConfigType;

typedef struct 
{
	standardConfigType standard;  		//
	orientConfigType orientation;	//
	filterConfigType filter;       	//

} vibrationSettingsType;

vibrationSettingsType cfg_s, *pcfg_s;
vibrationSettingsType vibrationSettingsFromInterface = {0};
mVt_filt_detect_Parameter_t detectCfg;



int main(void)
{
	cfg_s.filter = SUB_MENU_FILTER_CFG;
	cfg_s.standard = ESP1_CFG;
	cfg_s.orientation = VERTICAL_CFG;
	pcfg_s = &cfg_s;

	vibrationSettingsFromInterface = *pcfg_s;

	/* Step 1: Config Filter enable */
	detectCfg.filter_en = (pcfg_s->filter == SUB_MENU_FILTER_CFG) ? true : false;
	
	/* Step 2: Config threshold and valid axes by standard, valid axes by HW orientation*/
	const uint8_t *p_axis_votes = NULL;
	switch (pcfg_s->standard)
	{
	case CH1_CFG:
		detectCfg.threshold = ch1_thrhld;
		p_axis_votes = (pcfg_s->orientation == HORIZONTAL_CFG) ? ch1_horiz : ch1_vert;
		break;
	case CH2_CFG:
		detectCfg.threshold = ch2_thrhld;
		p_axis_votes = (pcfg_s->orientation == HORIZONTAL_CFG) ? ch2_horiz : ch2_vert;
		break;
	case CH3_CFG:
		detectCfg.threshold = ch3_thrhld;
		p_axis_votes = (pcfg_s->orientation == HORIZONTAL_CFG) ? ch3_horiz : ch3_vert;
		break;
	default:
		detectCfg.threshold = esp_thrhld;
		p_axis_votes = (pcfg_s->orientation == HORIZONTAL_CFG) ? asme_h : asme_v;	
		break;
	}
	memcpy(detectCfg.axis_votes, p_axis_votes, sizeof(uint8_t)*3);
	return 1;
}
