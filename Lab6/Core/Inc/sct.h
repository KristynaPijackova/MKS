/*
 * sct.h
 *
 *Header file to enable us writing stuff on 7-seg
 *  Created on: 7. 10. 2021
 *      Author: student
 */

#ifndef SCT_H_
#define SCT_H_

void sct_init(void);
void sct_led(uint32_t value);
void sct_value(uint16_t value, uint8_t led);

#endif /* SCT_H_ */
