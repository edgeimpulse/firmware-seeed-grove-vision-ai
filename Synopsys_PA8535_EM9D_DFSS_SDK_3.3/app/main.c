#if defined(EDGE_IMPULSE_VISIONAI)
#include <edge_impulse_visionai/edge_impulse_visionai.h>

int main(void)
{
	edge_impulse_visionai();
}
#elif defined(EDGE_IMPULSE_SENSECAP)
#include <edge_impulse_sensecap/edge_impulse_sensecap.h>

int main(void)
{
	edge_impulse_sensecap();
}
#else
#error "Unknown APP_TYPE"
#endif