
#include "SpriteFont.h"
#include "Image.h"
#include "ImageManager.h"
#include "TextureManager.h"
#include "KapSprite.h"
#include <xmllite.h>
#include <shlwapi.h>
#include <DebugOut.h>
#include <iterator>

//Loads a sprite font
SpriteFont::SpriteFont(std::string path)
{
	// <Load associated texture into TextureManager>
	TextureManager::Load((path + ".tga").c_str());
	ImageManager::Load(path, TextureManager::Get((path + ".tga").c_str()));

	// Parse associated XML file
	XMLtoCollection(path + ".xml");
}

SpriteFont::~SpriteFont()
{
	FontMapIt it;
	KapSprite* sf;
	for (it = this->fontmap.begin(); it != this->fontmap.end();)
	{
		if (this->fontmap.size() > 0) {
			sf = it->second;
			this->fontmap.erase(it++);
			delete sf;
		}
		else{
			it++;
		}
	}


}

void SpriteFont::XMLtoCollection(std::string filename)
{
	IXmlReader* reader = nullptr;
	IStream* readStream = nullptr;
	XmlNodeType nodeType;

	CreateXmlReader(IID_PPV_ARGS(&reader), nullptr);

	SHCreateStreamOnFile(filename.c_str(), STGM_READ, &readStream);

	reader->SetProperty(XmlReaderProperty_DtdProcessing, DtdProcessing_Prohibit);
	reader->SetInput(readStream);

	const wchar_t* stringValue = nullptr;
	unsigned int stringSize = 0;

	int key = 0;		// ASCII value
	int x = 0;		// x, y position of the glyph in texture
	int y = 0;
	int w = 0;		// width and height of the gluth in texture
	int h = 0;

	while (S_OK == reader->Read(&nodeType))
	{
		switch (nodeType)
		{
		case XmlNodeType::XmlNodeType_Element:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);

			if (wcscmp(stringValue, L"character") == 0)
			{
				//Gets ASCII value
				reader->MoveToAttributeByName(L"key", nullptr);
				reader->GetValue(&stringValue, &stringSize);
				key = _wtoi(stringValue);
			}
			else if (wcscmp(stringValue, L"x") == 0)
			{
				ElementTextToInt(reader, x);
			}
			else if (wcscmp(stringValue, L"y") == 0)
			{
				ElementTextToInt(reader, y);
			}
			else if (wcscmp(stringValue, L"width") == 0)
			{
				ElementTextToInt(reader, w);
			}
			else if (wcscmp(stringValue, L"height") == 0)
			{
				ElementTextToInt(reader, h);
			}
			else
			{
			}
		} break;

		case XmlNodeType::XmlNodeType_EndElement:
		{
			reader->GetQualifiedName(&stringValue, &stringSize);
			assert(stringValue);

			//If we are at the end of "character", we found everything we need for this char
			if (wcscmp(stringValue, L"character") == 0)
			{
				std::string path = filename.substr(0, filename.size() - 4); //get rid of .xml at the end of the pathname

				KapSprite* c = new KapSprite(path, x + 0.0f, y + 0.00f, w - 0.00f, h - 0.00f); //shave some off the top
				this->fontmap.insert({ key, c });
			}

		} break;

		//Don't care about these
		case XmlNodeType::XmlNodeType_Attribute:
		case XmlNodeType::XmlNodeType_CDATA:
		case XmlNodeType::XmlNodeType_Comment:
		case XmlNodeType::XmlNodeType_DocumentType:
		case XmlNodeType::XmlNodeType_None:
		case XmlNodeType::XmlNodeType_ProcessingInstruction:
		case XmlNodeType::XmlNodeType_Text:
		case XmlNodeType::XmlNodeType_Whitespace:
		case XmlNodeType::_XmlNodeType_Last:
		default:
		{} break;
		}
	}

	//Release COM objects
	if (readStream)
	{
		readStream->Release();
	}

	if (reader)
	{
		reader->Release();
	}
}

void SpriteFont::ElementTextToInt(IXmlReader* pReader, int& out)
{
	const wchar_t* stringValue = nullptr;
	UINT stringSize = 0;
	XmlNodeType nodeType;

	while (S_OK == pReader->Read(&nodeType))
	{
		if (nodeType == XmlNodeType::XmlNodeType_Text)
		{
			pReader->GetValue(&stringValue, &stringSize);
			assert(stringValue);

			out = _wtoi(stringValue);
			break;
		}
	}
}

SpriteFont::Glyph* SpriteFont::GetGlyph(char a)
{
	for (FontMapIt it = this->fontmap.begin(); it != this->fontmap.end(); ++it)
	{
		if (it->first == a)			//if key equals the character
		{
			return it->second;		//return glyph
		}
	}
	return this->fontmap.begin()->second;
}


