/*
    HTMLDataExtractor.cpp
*/

#include "HTMLDataExtractor.h"

using namespace HTMLData;

const std::string Extractor::HTML_DOC_TITLE = "ITI - Order Status Details.html";

bool Extractor::set_info(const char *filename)
{
    htmlDocPtr doc = htmlReadFile(filename, NULL, HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING);
    if (!doc)
    {
        std::cerr << "Failed to parse HTML file." << std::endl;
        return false;
    }

    xmlXPathContextPtr xpath_ctx = xmlXPathNewContext(doc);
    if (!xpath_ctx)
    {
        std::cerr << "Failed to create XPath context." << std::endl;
        xmlFreeDoc(doc);
        return false;
    }

    if (!valid_doc(xpath_ctx))
    {
        std::cerr << "Invalid HTML Document." << std::endl;
        xmlFreeDoc(doc);
        return false;
    }

    m_data.order_number = get_order_id_number(xpath_ctx);
    m_data.customer_name = get_customer_contact_field(xpath_ctx, "Name");
    m_data.customer_addr = get_customer_addr(xpath_ctx);
    m_data.customer_phone = get_customer_contact_field(xpath_ctx, "Phone No");
    m_data.customer_email = get_customer_contact_field(xpath_ctx, "Email");
    m_data.tv_manufacturer = get_product_information_field(xpath_ctx, "Manufacturer");
    m_data.tv_model = get_product_information_field(xpath_ctx, "Model#");
    m_data.tv_serial = get_product_information_field(xpath_ctx, "Serial#");
    m_data.problem_descr = get_problem_description(xpath_ctx);

    xmlXPathFreeContext(xpath_ctx);
    xmlFreeDoc(doc);

    return true;
}

ExtractedData Extractor::get_info()
{
    return m_data;
}

bool Extractor::valid_doc(xmlXPathContextPtr ctx)
{
    std::string xpath_expr = "//title[text()='" + HTML_DOC_TITLE + "']";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);
    if (!result)
    {
        xmlXPathFreeObject(result);
        std::cout << "Invalid HTML Document" << std::endl;
        return false;
    }
    xmlXPathFreeObject(result);
    return true;
}

std::string Extractor::get_order_id_number(xmlXPathContextPtr ctx)
{
    std::string xpath_expr = "//h4[text()='Order Status']/following-sibling::div//label[contains(text(), 'ID:')]/ancestor::tr/td[2]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);

    if (result && !xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        xmlChar *content = xmlNodeGetContent(node);
        std::string value = content ? (const char *)content : "";
        if (content)
        {
            xmlFree(content);
        }
        xmlXPathFreeObject(result);
        return value;
    }

    if (result)
    {
        xmlXPathFreeObject(result);
    }
    std::cout << "Order ID not found" << std::endl;
    return "ITI0000000";
}

std::string Extractor::get_customer_contact_field(xmlXPathContextPtr ctx, const std::string &label_text)
{
    std::string xpath_expr = "//h4[text()='Customer Contact']/following-sibling::div//label[contains(text(),'" + label_text + "')]/ancestor::tr/td[2]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);

    if (result && !xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        xmlChar *content = xmlNodeGetContent(node);
        std::string value = content ? (const char *)content : "";
        if (content)
        {
            xmlFree(content);
        }
        xmlXPathFreeObject(result);
        return value;
    }

    if (result)
    {
        xmlXPathFreeObject(result);
    }
    std::cout << "Customer contact field: " << label_text << " not found" << std::endl;
    return "Unk";
}

std::string Extractor::get_customer_addr(xmlXPathContextPtr ctx)
{
    std::string xpath_expr = "//h4[text()='Customer Contact']/following-sibling::div//label[contains(text(),'Address')]/ancestor::tr/td[2]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);

    if (result && !xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        std::string value = "";
        // Detect line break and insert newline character
        for (xmlNodePtr child = node->children; child; child = child->next)
        {
            if (child->type == XML_ELEMENT_NODE && xmlStrEqual(child->name, BAD_CAST "br"))
            {
                value += '\n';
            }
            else if (child->type == XML_TEXT_NODE)
            {
                xmlChar *content = xmlNodeGetContent(child);
                if (content)
                {
                    value += (const char *)content;
                    xmlFree(content);
                }
            }
        }
        xmlXPathFreeObject(result);
        return value;
    }

    if (result)
    {
        xmlXPathFreeObject(result);
    }
    std::cout << "Customer address not found" << std::endl;
    return "Unk";
}

std::string Extractor::get_product_information_field(xmlXPathContextPtr ctx, const std::string &label_text)
{
    std::string xpath_expr = "//h4[text()='Product Information']/following-sibling::div//label[contains(text(),'" + label_text + "')]/ancestor::tr/td[2]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);

    if (result && !xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        xmlChar *content = xmlNodeGetContent(node);
        std::string value = content ? (const char *)content : "";
        if (content)
        {
            xmlFree(content);
        }
        xmlXPathFreeObject(result);
        return value;
    }

    if (result)
    {
        xmlXPathFreeObject(result);
    }
    std::cout << "Product information field: " << label_text << " not found" << std::endl;
    return "Unk";
}

std::string Extractor::get_problem_description(xmlXPathContextPtr ctx)
{
    std::string xpath_expr = "//h4[text()='Order Description']/following-sibling::div//label[contains(text(), 'Problem Description')]/ancestor::tr/td[2]";
    xmlXPathObjectPtr result = xmlXPathEvalExpression((const xmlChar *)xpath_expr.c_str(), ctx);

    if (result && !xmlXPathNodeSetIsEmpty(result->nodesetval))
    {
        xmlNodePtr node = result->nodesetval->nodeTab[0];
        xmlChar *content = xmlNodeGetContent(node);
        std::string value = content ? (const char *)content : "";
        if (content)
        {
            xmlFree(content);
        }
        xmlXPathFreeObject(result);
        return value;
    }

    if (result)
    {
        xmlXPathFreeObject(result);
    }
    std::cout << "Problem description not found" << std::endl;
    return "Unk";
}