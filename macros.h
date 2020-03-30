#define set_bit(Var,BitNo) Var |=  (1 << BitNo)
#define clr_bit(Var,BitNo) Var &= ~(1 << BitNo)
#define tog_bit(Var,BitNo) Var ^=  (1 << BitNo)
#define get_bit(Var,BitNo) ((Var >> BitNo) & 1)
#define ass_bit(Var,BitNo,Val) (Val==0)? clr_bit(Var,BitNo):(set_bit(Var,BitNo))
#define set_HighNibble(Var) Var |= 240
#define set_LowNibble(Var) Var |= 15
#define clr_HighNibble(Var) Var &= 15
#define clr_LowNibble(Var) Var &= 240
#define ass_HighNibble(Var,Val) (Val==0)? clr_HighNibble(Var):(set_HighNibble(Var))
#define ass_LowNibble(Var,Val) (Val==0)? clr_LowNibble(Var):(set_LowNibble(Var))
#define NULL 0
