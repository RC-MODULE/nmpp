<?xml version="1.0" encoding="WINDOWS-1251"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:template match="/library">
		<table border="1">
		  <tr bgcolor="#CCCCCC">
			<!--<td align="center"><strong>N</strong></td>-->
			<td align="center"><strong>ipp-function</strong></td>
			<td align="center"><strong>nmc-analog</strong></td>
		  </tr>
		  <!-- выбираем функции-->
		  <xsl:apply-templates select="func">
			<!-- сортируем пустые функции-аналоги в конец-->
			<xsl:sort select="@analog = false()"/>
			<!-- сортируем функции-аналоги-->
			<xsl:sort select="@analog" order="ascending"/>
			<!-- сортируем функции-ipp-->
			<xsl:sort select="@name" order="ascending"/>
		  </xsl:apply-templates>
		</table>
	</xsl:template>

	<xsl:template match="func">
	  <tr bgcolor="#F5F5F5">
		<!--<td><xsl:value-of select="position()"/></td>-->
		<td><xsl:value-of select="@name"/></td>
		<td><xsl:value-of select="@analog"/></td>
	  </tr>
	</xsl:template>
</xsl:stylesheet>