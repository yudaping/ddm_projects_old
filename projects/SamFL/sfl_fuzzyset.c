/*
 *  sfl_fuzzyset.c
 *  samfl
 *
 *
 *      SamAI(umbrella) and SamFL provide a fuzzy-set-logic implementation in c.
 *      Copyright (C) 2005  Simon Andreas Menke
 *
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2.1 of the License, or (at your option) any later version.
 *
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 *
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library; if not, write to the Free Software
 *      Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *
 *      You can find the complete license in the lgpl-license.html(HTML version) and
 *      the lgpl-license.txt(TEXT version) files in the root directory of the project.
 *
 *
 *      e-mail: luinithil@luinithil.com
 *      site:   http://www.luinithil.com/
 *
 */


#include "sfl_fuzzyset.h"

#define max(x,y)        ((x > y) ? x : y)
#define min(x,y)        ((x < y) ? x : y)
#define cap(x)          max(min(x,1.0),0.0)

double sfl_and  (double rule_a, double rule_b) {
        return min(rule_a, rule_b);
}

double sfl_or   (double rule_a, double rule_b) {
        return max(rule_a, rule_b);
}

double sfl_nor  (double rule_a, double rule_b) {
        return 1.0 - max(rule_a, rule_b);
}

double sfl_nand (double rule_a, double rule_b) {
        return 1.0 - min(rule_a, rule_b);
}

double sfl_xor  (double rule_a, double rule_b) {
        return max(rule_a, rule_b) - min(rule_a, rule_b);
}

double sfl_not  (double rule) {
        return 1.0 - rule;
}


