/*
 * bits.h
 *
 * Created: 5/25/2019
 * Author: efosmark
 */
#ifndef BITS_H_
#define BITS_H_

#define bit_set(var, bitno) (var |=  (1 << bitno))
#define bit_get(var, bitno) (var & (1 << bitno))
#define bit_clear(var, bitno) (var &= ~(1 << bitno))

#endif /* BITS_H_ */
