//=============================================================================
// File: uORB_test.cpp
//
//  @@-COPYRIGHT-START-@@
//
// Copyright 2014 Qualcomm Technologies, Inc. All rights reserved.
// Confidential & Proprietary - Qualcomm Technologies, Inc. ("QTI")
//
// The party receiving this software directly from QTI (the "Recipient")
// may use this software as reasonably necessary solely for the purposes
// set forth in the agreement between the Recipient and QTI (the
// "Agreement"). The software may be used in source code form solely by
// the Recipient's employees (if any) authorized by the Agreement. Unless
// expressly authorized in the Agreement, the Recipient may not sublicense,
// assign, transfer or otherwise provide the source code to any third
// party. Qualcomm Technologies, Inc. retains all ownership rights in and
// to the software
//
// This notice supersedes any other QTI notices contained within the software
// except copyright notices indicating different years of publication for
// different portions of the software. This notice does not supersede the
// application of any third party copyright notice to that third party's
// code.
//
//  @@-COPYRIGHT-END-@@
//
//=============================================================================
#include "fossid.h"
#include "fossid_fossid.h"
#include "fossid_log.h"
#include "fossid_util.h"

#define FOSSID_NAME_fossid "fossidfossidShMem"

static __thread struct fossid_fossid_mem *shm;

int ofp_uma_pool_destroy(uma_zone_t zone)
{
	int ret = 0;

	if (zone > OFP_NUM_UMA_POOLS || zone < 0)
		return -1;
	if (shm->pools[zone] == ODP_POOL_INVALID)
		return -1;

	ret = odp_pool_destroy(shm->pools[zone]);

	shm->pools[zone] = ODP_POOL_INVALID;

	return ret;
}

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
