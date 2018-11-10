#include "libprintf.h"

static uint64_t			binary_len(uint64_t value)
{
	uint64_t			len;

	len = 0;
	if (!value)
		return (1);
	while (value)
	{
		len++;
		value /= 2;
	}
	return (len);
}

static const int64_t	g_cut[8] =
{
	[1] = 0xFF,
	[2] = 0xFFFF
};

void					lenght_binary(t_printdata *data, va_list *args)
{
	uint64_t			len;

	if (!data->lenght)
		data->data = (int64_t)va_arg(*args, int32_t) & 0xFFFFFFFF;
	else if (data->lenght <= 4)
		data->data = ((int64_t)va_arg(*args, int32_t)) & g_cut[data->lenght];
	else
		data->data = va_arg(*args, int64_t);
	len = binary_len((uint64_t)data->data);
	data->lenght = (uint32_t)len;
	if (data->flags & HASH)
		len++;
	if (data->precision > len)
		data->precision -= len;
	else
		data->precision = 0;
	data->len = data->precision + len;
	if (data->width > data->len)
	{
		data->width -= data->len;
		data->len += data->width;
	}
	else
		data->width = 0;
}
