<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/">
<meta charset="utf-8" /> 
<table border="1">
  <tr bgcolor="#CCCCCC">
	<td align="center"><strong>N</strong></td>
    <td align="center"><strong>Function</strong></td>
    <td align="center"><strong>Analog</strong></td>
    <td align="center"><strong>x86</strong></td>
	<td align="center"><strong>Test</strong></td>
	<td align="center"><strong>Restriction</strong></td>
	<td align="center"><strong>Performance</strong></td>
	<td align="center"><strong>Breif</strong></td>
  </tr>
  <xsl:for-each select="library/func" >
  <tr bgcolor="#F5F5F5">
	<td><xsl:value-of select="position()"/></td>
    <td><xsl:value-of select="@name"/></td>
    <td align="left"><xsl:value-of select="@nmc"/> </td>
    <td><xsl:value-of select="@x86"/></td>
	<td><xsl:value-of select="@test"/></td>
	<td><xsl:value-of select="@restr"/></td>
	<td><xsl:value-of select="@perf"/></td>
	<td><xsl:value-of select="@breif"/></td>
  </tr>
  </xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>