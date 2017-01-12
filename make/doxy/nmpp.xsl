<?xml version="1.0" encoding="WINDOWS-1251"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/">
<table border="1">
  <tr bgcolor="#CCCCCC">
    <td align="center"><strong>Function</strong></td>
    <td align="center"><strong>nmc</strong></td>
    <td align="center"><strong>x86</strong></td>
	<td align="center"><strong>Test</strong></td>
	<td align="center"><strong>Restriction</strong></td>
	<td align="center"><strong>Performance</strong></td>
	<td align="center"><strong>Documentation</strong></td>
  </tr>
  <xsl:for-each select="library/func" >
  <tr bgcolor="#F5F5F5">
    <td><xsl:value-of select="@name"/></td>
    <td align="left"><xsl:value-of select="@nmc"/> </td>
    <td><xsl:value-of select="@x86"/></td>
	<td><xsl:value-of select="@test"/></td>
	<td><xsl:value-of select="@restr"/></td>
	<td><xsl:value-of select="@perf"/></td>
	<td><xsl:value-of select="@doc"/></td>
  </tr>
  </xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>