#include "CR20MW.h"

std::vector<std::u16string> CR20MW::names = {
		AddComponent(u"CR20MW", []()
								 { return new CR20MW; }),
};

CR20MW::CR20MW()
{

	reader = new Reader;
	AddProperty(
			u"Version", u"ВерсияКомпоненты",
			[&](VH var)
			{ var = this->version(); });
	AddProperty(
			u"AuthorizationKeyMC", u"КлючАвторизацииMC",
			[&](VH var)
			{
				auto key = reader->GetKey();
				std::stringstream ss;
				for (int i = 0; i < 6; i++)
					ss << std::hex << (unsigned int)key[i];
				auto str = ss.str();
				// std::transform(str.begin(), str.end(), str.begin(), std::toupper);
				var = str;
			},
			[&](VH var)
			{ reader->SetKey(var); });
	AddFunction(
			u"GetLastError", u"ПолучитьОшибку", [&]()
			{ result = (int64_t)this->reader->GetLastError(); });
	AddFunction(u"ReadMifareC", u"ЧитатьMifareC", [&](VH handlev, VH sectorv, VH blockv, VH datav, VH block_countv, VH reader_keysv, VH keybv, VH skipv, VH timeoutv, VH key_posv)
							{ result = reader->Read(this, sectorv, blockv, block_countv, skipv); });
	AddProcedure(u"WriteMifareC", u"ПисатьMifareC", [&](VH handlev, VH sectorv, VH blockv, VH datav, VH block_countv, VH reader_keysv, VH keybv, VH skipv, VH timeoutv, VH key_posv)
							 {
								auto data = (std::vector<char>)datav; 
								reader->Write(this, sectorv, blockv, block_countv, skipv, &data); });
	AddProcedure(u"Message", u"Сообщить", [&]()
							 { AddError(u"Hello, World!"); });
}
