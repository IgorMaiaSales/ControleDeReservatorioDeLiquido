/*
 * pressão.h
 *
 *  Created on: Feb 16, 2022
 *      Author: rodri
 */

#ifndef INC_PRESSAO_H_
#define INC_PRESSAO_H_

float corrigePressao(float pressao);
float getPressao(float adc);
float getAltura(float pressao, float densidade);
float getCapacidade(float altura, float nivel);
float getDensidade(float temperatura);

#endif /* INC_PRESSAO_H_ */
