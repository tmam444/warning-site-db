/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_domain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:11:10 by chulee            #+#    #+#             */
/*   Updated: 2023/03/31 17:34:39 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "EnCrypt.h"

int main() {
	// char mesg[] = "http://sexefelin.com:80";
	char mesg[] = "https://metart.com:443";
	unsigned char result[16];

	//MD5 Hashing value of mesg is stored to array result!
	GetEncryptedMessage((unsigned char*)mesg,strlen(mesg),result);

	//Print result hashing value
	for( int i=0;i<16;i++)
		printf("%02X",result[i]);
	// printf("\n");

	/*
	if ( !IsEqual((unsigned char*)mesg,strlen(mesg),result) ) {
		printf("Hashing value of [%s] is not equal to result value!\n", mesg);
	}else {
		printf("Equal !!!\n");
	}
	*/
}
