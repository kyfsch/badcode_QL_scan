static void ag71xx_bit_clear(void __iomem *reg, u32 bit)
{
	u32 val;

	val = __raw_readl(reg) & ~bit;
	__raw_writel(val, reg);
	__raw_readl(reg);
}
