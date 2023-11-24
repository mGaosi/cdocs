/**
 * @file function.h
 * @author Jiangjie Gao (gaojiangjie@live.com)
 * @brief This is function brief
 *
 * This is function decription.
 *
 * @version 0.1
 * @date 2023-11-13
 *
 * @copyright Copyright (c) 2023
 *
 */

/**
 * @brief Typedef.
 */
typedef int int32_t;

/**
 * @brief Param of Teat.
 */
typedef struct _Teat
{
    const char* alias;   ///< Human friendly name.
    const char* local;   ///< Specific local network interface, like IP, adapter name ...
    const char* remote;  ///< Specific remote interface.
    const char* tags;    ///< Tags for stream.
} Teat;

/**
 * @brief The Function object
 *
 * This is Description.
 *
 */
void Function();

/**
 * @brief The Function 0 object
 *
 * @return int32_t
 */
int32_t Function0();

/**
 * @brief The Function 1 object
 *
 * @return int32_t
 */
int32_t Function1(int32_t a1);

/**
 * @brief The Function 2 object
 *
 * @return int32_t
 */
int32_t Function2(int32_t a1, const char* a2);
