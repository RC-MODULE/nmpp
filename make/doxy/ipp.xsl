<?xml version="1.0" encoding="WINDOWS-1251"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
<xsl:template match="/">
<table border="1">
  <tr bgcolor="#CCCCCC">
    <td align="center"><strong>ipp-function</strong></td>
    <td align="center"><strong>nmc-analog</strong></td>
  </tr>
  <xsl:for-each select="library/func" order-by="number(@analog)" >
  <tr bgcolor="#F5F5F5">
    <td><xsl:value-of select="@name"/></td>
    <td align="left"><xsl:value-of select="@nmc"/> </td>
    <td><xsl:value-of select="@analog"/></td>
  </tr>
  </xsl:for-each>
</table>
</xsl:template>
</xsl:stylesheet>