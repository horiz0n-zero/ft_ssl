#include "libprintf.h"

static void		push_binary(uint64_t value, char *dst)
{
	if (!value)
		*dst = '0';
	while (value)
	{
		*dst-- = value % 2 + 48;
		value /= 2;
	}
}

void			transform_binary(t_printdata *data, char *dst)
{
	const char	pad = !data->precision && data->flags & ZERO ? '0' : ' ';

	if (data->flags & MINUS)
	{
		if (data->flags & HASH)
			*dst++ = '0';
		while (data->precision-- > 0)
			*dst++ = '0';
		push_binary((uint64_t)data->data, (dst += data->lenght) - 1);
		while (data->width-- > 0)
			*dst++ = ' ';
	}
	else
	{
		while (data->width-- > 0)
			*dst++ = pad;
		while (data->precision-- > 0)
			*dst++ = '0';
		if (data->flags & HASH)
			*dst++ = '0';
		push_binary((uint64_t)data->data, (dst += data->lenght) - 1);
	}
}
