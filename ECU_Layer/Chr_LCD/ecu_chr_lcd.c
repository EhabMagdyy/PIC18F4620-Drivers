/* 
 * File:   ecu_chr_lcd.c
 * Author: Ehab
 *
 * Created on 30 ?????, 2023, 11:34 ?
 */

#include "ecu_chr_lcd.h"

static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd, uint8 data);
static Std_ReturnType send_4bit_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType send_8bit_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 colomn);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 colomn);

/**
 * 
 * @param lcd
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_intialize(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        for(uint8 pin = 0 ; pin < 4 ; pin++){
            ret = gpio_pin_intialize(&(lcd->data_lines[pin]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_4bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        
        ret = lcd_4bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_4bit_send_command(lcd, LCD_CURSOR_HOME);
        ret = lcd_4bit_send_command(lcd, LCD_INCREMENT_SHIFT_OFF);
        ret = lcd_4bit_send_command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_4bit_send_command(lcd, LCD_4BIT_MODE_2LINES);
        ret = lcd_4bit_send_command(lcd, LCD_DDRAM_START);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_command(const lcd_4bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bit(lcd, command >> 4);
        ret = send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, command);
        ret = send_4bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bit(lcd, data >> 4);
        ret = send_4bit_enable_signal(lcd);
        ret = lcd_send_4bit(lcd, data);
        ret = send_4bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_set_cursor(lcd, row, colomn);
        ret = lcd_4bit_send_char(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param string
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        do{
            lcd_4bit_send_char(lcd, *string);
        } while(*(++string));
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param string
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 row, uint8 colomn, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_set_cursor(lcd, row, colomn);
        ret = lcd_4bit_send_string(lcd, string);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param ch
 * @param mem_pos
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_4bit_send_custom_character(const lcd_4bit_t *lcd, uint8 row, uint8 colomn,
                                                const uint8 ch[], uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_4bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8 char_index = 0 ; char_index < 8 ; char_index++){
            ret = lcd_4bit_send_char(lcd, ch[char_index]);
        }
        ret = lcd_4bit_send_char_pos(lcd, row, colomn, mem_pos);
    }
    return ret;
}


/* ============  8_bit Mode  ============  */
/**
 * 
 * @param lcd
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_intialize(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_enable));
        for(uint8 pin = 0 ; pin < 8 ; pin++){
            ret = gpio_pin_intialize(&(lcd->data_lines[pin]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_ms(5);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        __delay_us(150);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        
        ret = lcd_8bit_send_command(lcd, LCD_CLEAR);
        ret = lcd_8bit_send_command(lcd, LCD_CURSOR_HOME);
        ret = lcd_8bit_send_command(lcd, LCD_INCREMENT_SHIFT_OFF);
        ret = lcd_8bit_send_command(lcd, LCD_DISPLAY_ON_UNDERLINE_OFF_CURSOR_OFF);
        ret = lcd_8bit_send_command(lcd, LCD_8BIT_MODE_2LINES);
        ret = lcd_8bit_send_command(lcd, LCD_DDRAM_START);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param command
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_command(const lcd_8bit_t *lcd, uint8 command){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        for(uint8 line_data_pin = 0 ; line_data_pin < 8 ; line_data_pin++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_data_pin]), (command >> line_data_pin) & 0x01);
        }
        ret = send_8bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        for(uint8 line_data_pin = 0 ; line_data_pin < 8 ; line_data_pin++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_data_pin]), (data >> line_data_pin) & 0x01);
        }
        ret = send_8bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_8bit_set_cursor(lcd, row, colomn);
        ret = lcd_8bit_send_char(lcd, data);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param string
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && NULL != string){
        ret = E_OK;
        do{
            lcd_8bit_send_char(lcd, *string);
        } while(*(++string));
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param string
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 row, uint8 colomn, uint8 *string){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_8bit_set_cursor(lcd, row, colomn);
        ret = lcd_8bit_send_string(lcd, string);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param ch
 * @param mem_pos
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_send_custom_character(const lcd_8bit_t *lcd, uint8 row, uint8 colomn,
                                                const uint8 ch[], uint8 mem_pos){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = lcd_8bit_send_command(lcd, (LCD_CGRAM_START + (mem_pos * 8)));
        for(uint8 char_index = 0 ; char_index < 8 ; char_index++){
            ret = lcd_8bit_send_char(lcd, ch[char_index]);
        }
        /* This function set cursor to it's previous one and display the character from CGRAM */
        ret = lcd_8bit_send_char_pos(lcd, row, colomn, mem_pos);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_8bit_read_data(const lcd_8bit_t *lcd,uint8 *data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK; 
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        uint8 logic = GPIO_LOW;
        for(uint8 data_line_index = 0 ; data_line_index < 8 ; data_line_index++){
            ret = gpio_pin_read_logic(&(lcd->data_lines[data_line_index]), &logic);
            *data = *data | (logic << data_line_index);
        }
        ret = send_8bit_enable_signal(lcd);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_convert_byte_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != str){
        ret = E_OK;
        memset(str, '\0', 4);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_convert_short_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != str){
        ret = E_OK;
        memset(str, '\0', 6);
        sprintf(str, "%i", value);
        
        /* ['2','3','4','\0','\0','\0'] -> ['2','3','4',' ',' ','\0'] */
        uint8 index = 0;
        while(++index < 5){
            if('\0' == str[index]){ str[index] = ' '; }
        }
    }
    return ret;
}

/**
 * 
 * @param value
 * @param str
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
Std_ReturnType lcd_convert_int_to_string(uint32 value, uint8 *str){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != str){
        ret = E_OK;
        memset(str, '\0', 11);
        sprintf(str, "%i", value);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param data
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
static Std_ReturnType lcd_send_4bit(const lcd_4bit_t *lcd, uint8 data){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        for(uint8 line_pins = 0 ; line_pins < 4 ; line_pins++){
            ret = gpio_pin_write_logic(&(lcd->data_lines[line_pins]), (data >> line_pins) & 0x01);
        }
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
static Std_ReturnType send_4bit_enable_signal(const lcd_4bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_LOW);
    }
    return ret;
}
/**
 * 
 * @param lcd
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
static Std_ReturnType send_8bit_enable_signal(const lcd_8bit_t *lcd){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd){
        ret = E_OK;
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write_logic(&(lcd->lcd_enable), GPIO_LOW);
    }
    return ret;
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 colomn){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && row <= NUMBER_OF_ROWS && colomn <= NUMBER_OF_COLOMNS){
        colomn--; //Start with index zero
        switch(row){
            case ROW1: ret = lcd_8bit_send_command(lcd, (0x80 + colomn));  break;
            case ROW2: ret = lcd_8bit_send_command(lcd, (0xc0 + colomn));  break;
            case ROW3: ret = lcd_8bit_send_command(lcd, (0x94 + colomn));  break;
            case ROW4: ret = lcd_8bit_send_command(lcd, (0xd4 + colomn));  break;
            default:                                                       break;
        }
    }
    return ret; 
}

/**
 * 
 * @param lcd
 * @param row
 * @param colomn
 * @return status of the function
 *         (E_OK): The function done successfully
 *         (E_NOT_OK): The function has issue to perform this action
 */
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 colomn){
    Std_ReturnType ret = E_NOT_OK;
    if(NULL != lcd && row <= NUMBER_OF_ROWS && colomn <= NUMBER_OF_COLOMNS){
        colomn--; //Start with index zero
        switch(row){
            case ROW1: ret = lcd_4bit_send_command(lcd, (0x80 + colomn));  break;
            case ROW2: ret = lcd_4bit_send_command(lcd, (0xc0 + colomn));  break;
            case ROW3: ret = lcd_4bit_send_command(lcd, (0x94 + colomn));  break;
            case ROW4: ret = lcd_4bit_send_command(lcd, (0xd4 + colomn));  break;
            default:                                                       break;
        }
    }
    return ret; 
}

