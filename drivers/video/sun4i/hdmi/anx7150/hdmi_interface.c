
#include "hdmi_interface.h"
#include <linux/cdev.h>
#include <linux/i2c.h>

static struct i2c_client *anx7150_client_0= NULL;
static struct i2c_client *anx7150_client_1 = NULL;
static unsigned char anx7150_reg = 0x04;  //default value is point to debug reg

static ssize_t show_reg(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	return sprintf(buf, "0x%x\n", anx7150_reg);
}

static ssize_t set_reg(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	u8 data = simple_strtoul(buf, NULL, 16);

	anx7150_reg = data;
	
	return count;
}

static DEVICE_ATTR(anx7150_reg, S_IWUSR | S_IRUGO, show_reg, set_reg);


static ssize_t show_read(struct device *dev, struct device_attribute *attr,
			 char *buf)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 data;
	int err;

	/* ������ֳ������֣�һ��Ϊд�豸�ڼĴ�����ַ��һ�������ݣ�
	�м���Բ���stop��start������IICЭ���Ҫ�� */
	err = i2c_master_send(client, &anx7150_reg, 1);
	if ( err < 0 ) 
	{
		__wrn("err meet when send reg addr in read\n");
		return err;
	}
	err = i2c_master_recv(client, &data, 1);
	if ( err < 0 )
	{
		__wrn("err meet when read data in read\n");
		return err;
	}

	return sprintf(buf, "%x\n", data);
}

static ssize_t set_write(struct device *dev, struct device_attribute *attr,
			 const char *buf, size_t count)
{
	struct i2c_client *client = to_i2c_client(dev);
	u8 data[2];
	int err;

	/* д����ֻ�ܵ�ַ������ͬʱ�������豸�ڼĴ�����ַ������
		�м䲻����start/stop/restart�ȳ��� */
	data[0] = anx7150_reg;
	data[1] = simple_strtoul(buf, NULL, 16);
	err = i2c_master_send(client, data, 2);
	if ( err < 0 )
	{
		__wrn("err meet when write\n");
		return err;
	}

	return count;
}

static DEVICE_ATTR(anx7150_iic, S_IWUSR | S_IRUGO, show_read, set_write);

static struct attribute *anx7150_iic_attributes[] = {
	&dev_attr_anx7150_iic.attr,
	&dev_attr_anx7150_reg.attr,
	NULL
};

static const struct attribute_group anx7150_iic_attr_group = {
	.attrs = anx7150_iic_attributes,
};


int ANX7150_i2c_read_p0_reg(u8 reg, __u8 *rt_value)
{
	struct i2c_client *client = anx7150_client_0;
	
	if (!client || !client->adapter)
	{
		__wrn("iic not exsit yet when read p0.\n");
		return -ENODEV;
	}

	*rt_value = i2c_smbus_read_byte_data(client,reg);

	return 0;
}

int ANX7150_i2c_read_p1_reg(u8 reg, __u8 *rt_value)
{
	struct i2c_client *client = anx7150_client_1;
	
	if (!client || !client->adapter)
	{
		__wrn("iic not exsit yet when read p1.\n");
		return -ENODEV;
	}

	if (!client || !client->adapter)
	{
		__wrn("iic not exsit yet when read p0.\n");
		return -ENODEV;
	}

	*rt_value = i2c_smbus_read_byte_data(client,reg);

	return 0;
}
int ANX7150_i2c_write_p0_reg(__u8 reg, __u8 d)
{
	struct i2c_client *client = anx7150_client_0;

	if (!client || !client->adapter)
	{
		__wrn("iic not exsit yet when write p0.\n");
		return -ENODEV;
	}

	i2c_smbus_write_byte_data(client,reg,d);

	return 0;
}
int ANX7150_i2c_write_p1_reg(__u8 reg, __u8 d)
{
	struct i2c_client *client = anx7150_client_1;

	if (!client || !client->adapter)
	{
		__wrn("iic not exsit yet when write p0.\n");
		return -ENODEV;
	}

	i2c_smbus_write_byte_data(client,reg,d);

	return 0;
}

static int anx7150_iic_probe_0(struct i2c_client *client,
			const struct i2c_device_id *id)
{
   int rc; 

   if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_I2C)) 
    {
	   __wrn("i2c bus does not support the IICDEV\n");
	   rc = -ENODEV;
	   goto exit;
   }
	rc = sysfs_create_group(&client->dev.kobj, &anx7150_iic_attr_group);
   anx7150_client_0= client;
   anx7150_client_0->addr /= 2;
   
exit:
   return rc;
}

static int anx7150_iic_probe_1(struct i2c_client *client,
			const struct i2c_device_id *id)
{
   int rc; 

   if (!i2c_check_functionality(client->adapter,
					I2C_FUNC_I2C)) {
	   __wrn("i2c bus does not support the IICDEV\n");
	   rc = -ENODEV;
	   goto exit;
   }
   anx7150_client_1= client;
   anx7150_client_1->addr /= 2;
   
exit:
   return rc;
}

static int anx7150_iic_remove_0(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &anx7150_iic_attr_group);
	anx7150_client_0 = NULL;
	return 0;
}


static int anx7150_iic_remove_1(struct i2c_client *client)
{
	anx7150_client_1 = NULL;
	return 0;
}

static const struct i2c_device_id anx7150_iic_id_0[] = {
	{ "anx7150_0", 0 },
	{ }
};

static const struct i2c_device_id anx7150_iic_id_1[] = {
	{ "anx7150_1", 0 },
	{ }
};

MODULE_DEVICE_TABLE(i2c,  anx7150_iic_id_0);
MODULE_DEVICE_TABLE(i2c,  anx7150_iic_id_1);

static struct i2c_driver anx7150_iic_driver_0 = {
	.driver = {
		.name = "anx7150_0",
	},
	.probe = anx7150_iic_probe_0,
	.remove = anx7150_iic_remove_0,
	.id_table = anx7150_iic_id_0,
};

static struct i2c_driver anx7150_iic_driver_1 = {
	.driver = {
		.name = "anx7150_1",
	},
	.probe = anx7150_iic_probe_1,
	.remove = anx7150_iic_remove_1,
	.id_table = anx7150_iic_id_1,
};

__s32 hdmi_i2c_add_driver(void)
{
    __s32 ret = 0;

    ret |= i2c_add_driver(&anx7150_iic_driver_0);
	ret |= i2c_add_driver(&anx7150_iic_driver_1);

    return ret;
}


__s32 hdmi_i2c_del_driver(void)
{
    i2c_del_driver(&anx7150_iic_driver_0);
	i2c_del_driver(&anx7150_iic_driver_1);

    return 0;
}

