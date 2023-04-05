/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_domain.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chulee <chulee@nstek.com>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:11:10 by chulee            #+#    #+#             */
/*   Updated: 2023/04/05 11:08:57 by chulee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "site_db_table.h"
#include "EnCrypt.h"

unsigned int	collision_count[TABLE_COUNT];

void convert_to_hex_string(unsigned char *input, char *output, int length)
{
    for (int i = 0; i < length; i++)
    {
        sprintf(output + (i * 2), "%02X", input[i]);
    }
}

int main() {
	// char mesg[] = "http://sexefelin.com:80";
	char mesg[] = "https://metart.com:443";
	unsigned char result[16];
	char		output[33];

	//MD5 Hashing value of mesg is stored to array result!
	GetEncryptedMessage((unsigned char*)mesg,strlen(mesg),result);

	//Print result hashing value
	for( int i=0;i<16;i++)
		printf("%02X",result[i]);
	printf("\n");
	for( int i=0;i<16;i++)
		printf("%X ",result[i]);
	convert_to_hex_string(result, output, 16);
	output[32] = '\0';
	printf("Hexadecimal string: %s\n", output);
	
	// printf("\n");

	if ( !IsEqual((unsigned char*)mesg,strlen(mesg),result) ) {
		printf("Hashing value of [%s] is not equal to result value!\n", mesg);
	}else {
		printf("Equal !!!\n");
	}
}
