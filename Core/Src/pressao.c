/*
 * pressao.c
 *
 *  Created on: Feb 14, 2022
 *      @author Rodrigo Hiury
 */

#include "pressao.h"
#include "math.h"

/*
 * @brief corrige o valor da pressão medida pelo adc
 * @param pressão calculada pela função getPressao
 * @retval valor da pressão corrigida
 */

float corrigePressao(float pressao){
	return -6.1048283274439417e+000
			+ 1.2990936811532654e+000 * pressao
			+ 6.0765816418719276e-005 * pressao * pressao;
}

/*
 * @brief calcula pressão com o valor lido pelo adc. Configurado para o sensor MPX4115A
 * @retval valor da pressao em kPa
 */

float getPressao(float adc){
	float pressao;
	adc /= 204.8;
	adc += 0.475;
    adc /= 0.045;
    adc -=  1.3;
    adc *= 0.94148052;
    adc /= 100;
    pressao = (((adc/5.1)+0.095)/0.009)*0.93692308;
    return corrigePressao(pressao);
}

/*
 * @brief calcula altura do liquido do reservatório
 * @param pressao: valor da pressao lida pelo sensor
 * @param densidade: densidade do líquido do reservatorio
 * @retval altura do liquido no reservatorio em metros
 */

float getAltura(float pressao, float densidade){
	pressao *= 1000;
	return (pressao/(densidade*9.81)); // considera gravidade da terra igual a 9.81
}

/*
 * @brief calcula a capacidade ocupada no reservatorio
 * @param altura: altura máxima de capacidade do reservatorio
 * @param nivel: altura atual ocupada no reservatorio
 * @retval capacidade ocupada no reservatorio em porcentagem
 */

float getCapacidade(float altura, float nivel){
	return ((nivel/altura)*100);
}

/*
 * @brief Calcula a densidade da água de acordo com a temperatura
 *
 * @param temperatura: temperatura em graus celcius
 * @retval densidade da agua em kg/m3
 */

float getDensidade(float temperatura){
	float d = 9.9998296349897953e-001+1.0044593739780175e-005*temperatura-5.0243729029104561e-006*temperatura*temperatura;
	return d*1000;
}
