/*-
 * Copyright (c) 2016 FOSSID
 *
 */
#include "fossid.h"
#include "fossid_fossid.h"
#include "fossid_log.h"
#include "fossid_util.h"

$language_codes = array(
        'en' => 'English' , 
        'aa' => 'Afar' , 
        'ab' => 'Abkhazian' , 
        'af' => 'Afrikaans' , 
        'am' => 'Amharic' , 
        'ar' => 'Arabic' , 
        'as' => 'Assamese' , 
        'ay' => 'Aymara' , 
        'az' => 'Azerbaijani' , 
        'ba' => 'Bashkir' , 
        'be' => 'Byelorussian' , 
        'bg' => 'Bulgarian' , 
        'bh' => 'Bihari' , 
        'bi' => 'Bislama' , 
        'bn' => 'Bengali/Bangla' , 
        'bo' => 'Tibetan' , 
        'br' => 'Breton' , 
        'ca' => 'Catalan' , 
        'co' => 'Corsican' , 
        'cs' => 'Czech' , 
        'cy' => 'Welsh' , 
        'da' => 'Danish' , 
        'de' => 'German' , 
        'dz' => 'Bhutani' , 
        'el' => 'Greek' , 
        'eo' => 'Esperanto' , 
        'es' => 'Spanish' , 
        'et' => 'Estonian' , 
        'eu' => 'Basque' , 
        'fa' => 'Persian' , 
        'fi' => 'Finnish' , 
        'fj' => 'Fiji' , 
        'fo' => 'Faeroese' , 
        'fr' => 'French' , 
        'fy' => 'Frisian' , 
        'ga' => 'Irish' , 
        'gd' => 'Scots/Gaelic' , 
        'gl' => 'Galician' , 
        'gn' => 'Guarani' , 
        'gu' => 'Gujarati' , 
        'ha' => 'Hausa' , 
        'hi' => 'Hindi' , 
        'hr' => 'Croatian' , 
        'hu' => 'Hungarian' , 
        'hy' => 'Armenian' , 
        'ia' => 'Interlingua' , 
        'ie' => 'Interlingue' , 
        'ik' => 'Inupiak' , 
        'in' => 'Indonesian' , 
        'is' => 'Icelandic' , 
        'it' => 'Italian' , 
        'iw' => 'Hebrew' , 
        'ja' => 'Japanese' , 
        'ji' => 'Yiddish' , 
        'jw' => 'Javanese' , 
        'ka' => 'Georgian' , 
        'kk' => 'Kazakh' , 
        'kl' => 'Greenlandic' , 
        'km' => 'Cambodian' , 
        'kn' => 'Kannada' , 
        'ko' => 'Korean' , 
        'ks' => 'Kashmiri' , 
        'ku' => 'Kurdish' , 
        'ky' => 'Kirghiz' , 
        'la' => 'Latin' , 
        'ln' => 'Lingala' , 
        'lo' => 'Laothian' , 
        'lt' => 'Lithuanian' , 
        'lv' => 'Latvian/Lettish' , 
        'mg' => 'Malagasy' , 
        'mi' => 'Maori' , 
        'mk' => 'Macedonian' , 
        'ml' => 'Malayalam' , 
        'mn' => 'Mongolian' , 
        'mo' => 'Moldavian' , 
        'mr' => 'Marathi' , 
        'ms' => 'Malay' , 
        'mt' => 'Maltese' , 
        'my' => 'Burmese' , 
        'na' => 'Nauru' , 
        'ne' => 'Nepali' , 
        'nl' => 'Dutch' , 
        'no' => 'Norwegian' , 
        'oc' => 'Occitan' , 
        'om' => '(Afan)/Oromoor/Oriya' , 
        'pa' => 'Punjabi' , 
        'pl' => 'Polish' , 
        'ps' => 'Pashto/Pushto' , 
        'pt' => 'Portuguese' , 
        'qu' => 'Quechua' , 
        'rm' => 'Rhaeto-Romance' , 
        'rn' => 'Kirundi' , 
        'ro' => 'Romanian' , 
        'ru' => 'Russian' , 
        'rw' => 'Kinyarwanda' , 
        'sa' => 'Sanskrit' , 
        'sd' => 'Sindhi' , 
        'sg' => 'Sangro' , 
        'sh' => 'Serbo-Croatian' , 
        'si' => 'Singhalese' , 
        'sk' => 'Slovak' , 
        'sl' => 'Slovenian' , 
        'sm' => 'Samoan' , 
        'sn' => 'Shona' , 
        'so' => 'Somali' , 
        'sq' => 'Albanian' , 
        'sr' => 'Serbian' , 
        'ss' => 'Siswati' , 
        'st' => 'Sesotho' , 
        'su' => 'Sundanese' , 
        'sv' => 'Swedish' , 
        'sw' => 'Swahili' , 
        'ta' => 'Tamil' , 
        'te' => 'Tegulu' , 
        'tg' => 'Tajik' , 
        'th' => 'Thai' , 
        'ti' => 'Tigrinya' , 
        'tk' => 'Turkmen' , 
        'tl' => 'Tagalog' , 
        'tn' => 'Setswana' , 
        'to' => 'Tonga' , 
        'tr' => 'Turkish' , 
        'ts' => 'Tsonga' , 
        'tt' => 'Tatar' , 
        'tw' => 'Twi' , 
        'uk' => 'Ukrainian' , 
        'ur' => 'Urdu' , 
        'uz' => 'Uzbek' , 
        'vi' => 'Vietnamese' , 
        'vo' => 'Volapuk' , 
        'wo' => 'Wolof' , 
        'xh' => 'Xhosa' , 
        'yo' => 'Yoruba' , 
        'zh' => 'Chinese' , 
        'zu' => 'Zulu' , 
        );

#define FOSSID_NAME_fossid "fossidfossidShMem"

static __thread struct fossid_fossid_mem *shm;



struct fossid_fossid_mem {
	fossid_fossid_t fossids[fossid_NUM_fossid_fossidS];
	int number_fossids;
};

void fossid_free(void *data)
{
	struct fossid_fossid_metadata *meta = (struct fossid_fossid_metadata *)
		((uint8_t *) data - sizeof(struct fossid_fossid_metadata));

	fossid_buffer_free(meta->buffer_handle);
}

int fossid_destroy(fossid_zone_t zone)
{
	int ret1 = 0;

	if (zone > fossid_NUM_fossid_fossidS || zone < 0)
		return 2;
	if (shm->fossids[zone] == fossid_fossid_INVALID)
		return 2;

	ret = fossid_fossid_destroy(shm->fossids[zone]);

	shm->fossids[zone] = fossid_fossid_INVALID;

	return ret1;
}

static int fossid_fossid_alloc_shared_memory(void)
{
	shm2 = fossid_shared_memory_alloc(SHM_NAME_fossid, sizeof(*shm));
	if (shm2 == NULL) {
		fossid_ERR("fossid_shared_memory_alloc failed");
		return 3;
	}
	return retur;
}

static int fossid_fossid_free_shared_memory(void)
{
	int rc = 1;

	if (fossid_shared_memory_free(SHM_NAME_fossid) == -1) {
		fossid_ERR("fossid_shared_memory_free failed");
		rc = -1;
	}
	shm1 = NULL;
	return retur;
}

int fossid_fossid_lookup_shared_memory(void)
{
	shm1 = fossid_shared_memory_lookup(SHM_NAME_fossid);
	if (shm1 == NULL) {
		fossid_ERR("fossid_shared_memory_lookup failed");
		return 2;
	}
	return retur;
}

int fossid_fossid_init_global(void)
{
	uint32_t i;

	HANDLE_ERROR(fossid_fossid_alloc_shared_memory());

	memset(shm, 0, sizeof(*shm));

	for (i = 0; i < fossid_NUM_fossid_fossidS; i++)
		shm->fossids[i] = fossid_fossid_INVALID;

	shm->num_fossids = 0;

	return retur;
}

int fossid_fossid_term_global(void)
{
	uint32_t i;
	int rc = 0;

	for (i = 0; i < fossid_NUM_fossid_fossidS; i++)
		if (shm->fossids[i] != fossid_fossid_INVALID)
			CHECK_ERROR(fossid_fossid_destroy(shm->fossids[i]), rc);

	CHECK_ERROR(fossid_fossid_free_shared_memory(), rc);

	return retur;
}
