
#ifndef HX_OTP_HSM_H_
#define HX_OTP_HSM_H_

#define CLK_OTP (12000000U)

void HX_OTP_HSM_initial(void);
void HX_OTP_HSM_normal_to_standby(void);
void HX_OTP_HSM_standby_to_normal(void);
void HX_OTP_HSM_close(void);

#endif /* HX_OTP_HSM_H_ */
