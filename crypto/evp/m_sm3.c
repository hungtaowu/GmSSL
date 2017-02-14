/* ====================================================================
 * Copyright (c) 2014 - 2016 The GmSSL Project.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. All advertising materials mentioning features or use of this
 *    software must display the following acknowledgment:
 *    "This product includes software developed by the GmSSL Project.
 *    (http://gmssl.org/)"
 *
 * 4. The name "GmSSL Project" must not be used to endorse or promote
 *    products derived from this software without prior written
 *    permission. For written permission, please contact
 *    guanzhi1980@gmail.com.
 *
 * 5. Products derived from this software may not be called "GmSSL"
 *    nor may "GmSSL" appear in their names without prior written
 *    permission of the GmSSL Project.
 *
 * 6. Redistributions of any form whatsoever must retain the following
 *    acknowledgment:
 *    "This product includes software developed by the GmSSL Project
 *    (http://gmssl.org/)"
 *
 * THIS SOFTWARE IS PROVIDED BY THE GmSSL PROJECT ``AS IS'' AND ANY
 * EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE GmSSL PROJECT OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 * ====================================================================
 */

#include <stdio.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/objects.h>
#include "internal/cryptlib.h"
#include "internal/evp_int.h"

#ifndef OPENSSL_NO_SM3
# include <openssl/sm3.h>

static int init(EVP_MD_CTX *ctx)
{
	if (!ctx || !EVP_MD_CTX_md_data(ctx)) {
		return 0;
	}
	sm3_init(EVP_MD_CTX_md_data(ctx));
	return 1;
}

static int update(EVP_MD_CTX *ctx, const void *in, size_t inlen)
{
	if (!ctx || !EVP_MD_CTX_md_data(ctx) || !in) {
		return 0;
	}
	sm3_update(EVP_MD_CTX_md_data(ctx), in, inlen);
	return 1;
}

static int final(EVP_MD_CTX *ctx, unsigned char *md)
{
	if (!ctx || !EVP_MD_CTX_md_data(ctx) || !md) {
		return 0;
	}
	sm3_final(EVP_MD_CTX_md_data(ctx), md);
	return 1;
}

static const EVP_MD sm3_md = {
	NID_sm3,
	NID_sm2sign_with_sm3,
	SM3_DIGEST_LENGTH,
	0, /* flags */
	init,
	update,
	final,
	NULL,
	NULL,
	SM3_BLOCK_SIZE,
	sizeof(EVP_MD *) + sizeof(sm3_ctx_t),
};

const EVP_MD *EVP_sm3(void)
{
        return &sm3_md;
}
#endif /* OPENSSL_NO_SM3 */
