typedef unsigned char u8;
typedef unsigned short int u16;
typedef unsigned long int u32;
typedef signed char s8;
typedef signed short int s16;
typedef signed long int s32;
typedef float f32;
typedef double f64;

#define ISR(x) void vect(x) (void) __attribute__((signal)); \
               void vect(x) (void)

#define vect(x) __vector_##x

#define ISR_INT0 1
#define ISR_INT1 2
#define ISR_INT2 3
#define ISR_TIMER2_COMP  4
#define ISR_TIMER2_OVF   5
#define ISR_TIMER1_CAPT  6
#define ISR_TIMER1_COMPA 7
#define ISR_TIMER1_COMPB 8
#define ISR_TIMER1_OVF   9
#define ISR_TIMER0_COMP  10
#define ISR_TIMER0_OVF   11

