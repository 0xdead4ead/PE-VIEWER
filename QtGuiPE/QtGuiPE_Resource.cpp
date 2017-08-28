#include "QtGuiPE_Resource.h"
#include "PE_FILE1.h"
QtGuiPE_Resource::QtGuiPE_Resource(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

void QtGuiPE_Resource::fill_fields() {
	DWORD RVA;
	if (file.PE32)
		RVA = file.op_header32->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress;
	else
		RVA = file.op_header64->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE].VirtualAddress;

	if (RVA) {
		for (int i = 0; i < file.resources.size(); i++) {
			QTreeWidgetItem *item = new QTreeWidgetItem(ui.treeWidget);
			if ((ULONG_PTR)file.resources[i].lpszType & 0xFFFFFFFFFFFF0000) //program is 64 bit only
				item->setText(0, QString::fromWCharArray(file.resources[i].szResType.c_str()));
			else {
				switch (LOWORD(file.resources[i].lpszType)) {
				case LOWORD(RT_ACCELERATOR):
					item->setText(0, QString::fromWCharArray(_T("RT_ACCELERATOR"))); break;
				case  LOWORD(RT_BITMAP):
					item->setText(0, QString::fromWCharArray(_T("RT_BITMAP"))); break;
				case  LOWORD(RT_DIALOG):
					item->setText(0, QString::fromWCharArray(_T("RT_DIALOG"))); break;
				case  LOWORD(RT_FONT):
					item->setText(0, QString::fromWCharArray(_T("RT_FONT"))); break;
				case  LOWORD(RT_FONTDIR):
					item->setText(0, QString::fromWCharArray(_T("RT_FONTDIR"))); break;
				case  LOWORD(RT_MENU):
					item->setText(0, QString::fromWCharArray(_T("RT_MENU"))); break;
				case  LOWORD(RT_RCDATA):
					item->setText(0, QString::fromWCharArray(_T("RT_RCDATA"))); break;
				case  LOWORD(RT_STRING):
					item->setText(0, QString::fromWCharArray(_T("RT_STRING"))); break;
				case  LOWORD(RT_MESSAGETABLE):
					item->setText(0, QString::fromWCharArray(_T("RT_MESSAGETABLE"))); break;
				case  LOWORD(RT_CURSOR):
					item->setText(0, QString::fromWCharArray(_T("RT_CURSOR"))); break;
				case  LOWORD(RT_GROUP_CURSOR):
					item->setText(0, QString::fromWCharArray(_T("RT_GROUP_CURSOR"))); break;
				case  LOWORD(RT_ICON):
					item->setText(0, QString::fromWCharArray(_T("RT_ICON"))); break;
				case  LOWORD(RT_GROUP_ICON):
					item->setText(0, QString::fromWCharArray(_T("RT_GROUP_ICON"))); break;
				case  LOWORD(RT_VERSION):
					item->setText(0, QString::fromWCharArray(_T("RT_VERSION"))); break;
				case  LOWORD(RT_HTML):
					item->setText(0, QString::fromWCharArray(_T("RT_HTML"))); break;
				case  LOWORD(RT_MANIFEST):
					item->setText(0, QString::fromWCharArray(_T("RT_MANIFEST"))); break;
				case  LOWORD(RT_VXD):
					item->setText(0, QString::fromWCharArray(_T("RT_VXD"))); break;
				default:
					item->setText(0, QString::fromWCharArray(_T("UNKNOWN"))); break;
				}
			}
				


			item->setIcon(0, QPixmap(":/QtGuiPE_Resource/Resources/folder.bmp"));
			for (int j = 0; j < file.resources[i].names.size(); j++) {
				QTreeWidgetItem *item2 = new QTreeWidgetItem(item);
				if ((ULONG_PTR)file.resources[i].names[j].lpszName & 0xFFFFFFFFFFFF0000)
					item2->setText(0, QString::fromWCharArray(file.resources[i].names[j].szResName.c_str()));
				else
					item2->setText(0, QString::number(LOWORD(file.resources[i].names[j].lpszName)));
				item2->setIcon(0, QPixmap(":/QtGuiPE_Resource/Resources/resource-icon.png"));
				DWORD RVAoffset = file.resources[i].names[j].RVAData;
				DWORD RAWoffset = rvaToOff(&file.section_headers, file.resources[i].names[j].RVAData, 
					file.PE32 ? file.op_header32->SectionAlignment : file.op_header64->SectionAlignment);
				item2->setText(1, QString("%1").arg(RVAoffset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
				item2->setText(2, QString("%1").arg(RAWoffset, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
				item2->setText(3, QString("%1").arg(file.resources[i].names[j].ResourceSize, sizeof(DWORD) * 2, 16, QLatin1Char('0')).toUpper());
				switch (file.resources[i].names[j].wIDLanguage) {
					//https://msdn.microsoft.com/en-us/library/windows/desktop/dd318693(v=vs.85).aspx
				case LANG_BOSNIAN_NEUTRAL: 
					item2->setText(4, QString("LANG_BOSNIAN_NEUTRAL")); break;
				
				case LANG_CHINESE_TRADITIONAL:
					item2->setText(4, QString("LANG_CHINESE_TRADITIONAL")); break;
				case LANG_SERBIAN_NEUTRAL:
					item2->setText(4, QString("LANG_SERBIAN_NEUTRAL")); break;
				default: {

					switch (PRIMARYLANGID(file.resources[i].names[j].wIDLanguage)) {
					case LANG_NEUTRAL: {
						item2->setText(4, QString("LANG_NEUTRAL"));
						switch(SUBLANGID(file.resources[i].names[j].wIDLanguage)){
						case SUBLANG_NEUTRAL                             :item2->setText(5, QString("SUBLANG_NEUTRAL")); break;
						case SUBLANG_CUSTOM_DEFAULT                      :item2->setText(5, QString("SUBLANG_CUSTOM_DEFAULT")); break;
						case SUBLANG_CUSTOM_UNSPECIFIED                  :item2->setText(5, QString("SUBLANG_CUSTOM_UNSPECIFIED")); break;
						case SUBLANG_UI_CUSTOM_DEFAULT                   :item2->setText(5, QString("SUBLANG_UI_CUSTOM_DEFAULT")); break;
						default                                          :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_INVARIANT: {
						item2->setText(4, QString("LANG_INVARIANT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_NEUTRAL                             :item2->setText(5, QString("SUBLANG_NEUTRAL")); break;
						default                                          :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_SYSTEM_DEFAULT: {
						item2->setText(4, QString("LANG_SYSTEM_DEFAULT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SYS_DEFAULT                         :item2->setText(5, QString("SUBLANG_SYS_DEFAULT")); break;
						default                                          :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_USER_DEFAULT: {
						item2->setText(4, QString("LANG_USER_DEFAULT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_DEFAULT                             :item2->setText(5, QString("SUBLANG_DEFAULT")); break;
						default                                          :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_AFRIKAANS: {
						item2->setText(4, QString("LANG_AFRIKAANS"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_AFRIKAANS_SOUTH_AFRICA             :item2->setText(5, QString("SUBLANG_AFRIKAANS_SOUTH_AFRICA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ALBANIAN: {
						item2->setText(4, QString("LANG_ALBANIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ALBANIAN_ALBANIA                   :item2->setText(5, QString("SUBLANG_ALBANIAN_ALBANIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ALSATIAN: {
						item2->setText(4, QString("LANG_ALSATIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ALSATIAN_FRANCE                    :item2->setText(5, QString("SUBLANG_ALSATIAN_FRANCE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_AMHARIC: {
						item2->setText(4, QString("LANG_AMHARIC"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_AMHARIC_ETHIOPIA                   :item2->setText(5, QString("SUBLANG_AMHARIC_ETHIOPIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ARABIC: {
						item2->setText(4, QString("LANG_ARABIC"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ARABIC_ALGERIA                     :item2->setText(5, QString("SUBLANG_ARABIC_ALGERIA")); break;
						case SUBLANG_ARABIC_BAHRAIN                     :item2->setText(5, QString("SUBLANG_ARABIC_BAHRAIN")); break;
						case SUBLANG_ARABIC_EGYPT                       :item2->setText(5, QString("SUBLANG_ARABIC_EGYPT")); break;
						case SUBLANG_ARABIC_IRAQ                        :item2->setText(5, QString("SUBLANG_ARABIC_IRAQ")); break;
						case SUBLANG_ARABIC_JORDAN                      :item2->setText(5, QString("SUBLANG_ARABIC_JORDAN")); break;
						case SUBLANG_ARABIC_KUWAIT                      :item2->setText(5, QString("SUBLANG_ARABIC_KUWAIT")); break;
						case SUBLANG_ARABIC_LEBANON                     :item2->setText(5, QString("SUBLANG_ARABIC_LEBANON")); break;
						case SUBLANG_ARABIC_LIBYA                       :item2->setText(5, QString("SUBLANG_ARABIC_LIBYA")); break;
						case SUBLANG_ARABIC_MOROCCO                     :item2->setText(5, QString("SUBLANG_ARABIC_MOROCCO")); break;
						case SUBLANG_ARABIC_OMAN                        :item2->setText(5, QString("SUBLANG_ARABIC_OMAN")); break;
						case SUBLANG_ARABIC_QATAR                       :item2->setText(5, QString("SUBLANG_ARABIC_QATAR")); break;
						case SUBLANG_ARABIC_SAUDI_ARABIA                :item2->setText(5, QString("SUBLANG_ARABIC_SAUDI_ARABIA")); break;
						case SUBLANG_ARABIC_SYRIA                       :item2->setText(5, QString("SUBLANG_ARABIC_SYRIA")); break;
						case SUBLANG_ARABIC_TUNISIA                     :item2->setText(5, QString("SUBLANG_ARABIC_TUNISIA")); break;
						case SUBLANG_ARABIC_UAE                         :item2->setText(5, QString("SUBLANG_ARABIC_UAE")); break;
						case SUBLANG_ARABIC_YEMEN                       :item2->setText(5, QString("SUBLANG_ARABIC_YEMEN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ARMENIAN: {
						item2->setText(4, QString("LANG_ARMENIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ARMENIAN_ARMENIA                   :item2->setText(5, QString("SUBLANG_ARMENIAN_ARMENIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ASSAMESE: {
						item2->setText(4, QString("LANG_ASSAMESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ASSAMESE_INDIA                     :item2->setText(5, QString("SUBLANG_ASSAMESE_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_AZERI: {
						item2->setText(4, QString("LANG_AZERI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_AZERI_CYRILLIC                     :item2->setText(5, QString("SUBLANG_AZERI_CYRILLIC")); break;
						case SUBLANG_AZERI_LATIN                        :item2->setText(5, QString("SUBLANG_AZERI_LATIN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_BANGLA: {
						item2->setText(4, QString("LANG_BANGLA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BANGLA_BANGLADESH                  :item2->setText(5, QString("SUBLANG_BANGLA_BANGLADESH")); break;
						case SUBLANG_BANGLA_INDIA                       :item2->setText(5, QString("SUBLANG_BANGLA_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_BASHKIR: {
						item2->setText(4, QString("LANG_BASHKIR"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BASHKIR_RUSSIA                     :item2->setText(5, QString("SUBLANG_BASHKIR_RUSSIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_BASQUE: {
						item2->setText(4, QString("LANG_BASQUE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BASQUE_BASQUE                      :item2->setText(5, QString("SUBLANG_BASQUE_BASQUE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_BELARUSIAN: {
						item2->setText(4, QString("LANG_BELARUSIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BELARUSIAN_BELARUS                 :item2->setText(5, QString("SUBLANG_BELARUSIAN_BELARUS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_BRETON: {
						item2->setText(4, QString("LANG_BRETON"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BRETON_FRANCE                      :item2->setText(5, QString("SUBLANG_BRETON_FRANCE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_BOSNIAN: {
						item2->setText(4, QString("LANG_BOSNIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC:item2->setText(5, QString("SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_CYRILLIC")); break;
						case SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN:item2->setText(5, QString("SUBLANG_BOSNIAN_BOSNIA_HERZEGOVINA_LATIN")); break;
						default:item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_BOSNIAN_NEUTRAL: {
						item2->setText(4, QString("LANG_BOSNIAN_NEUTRAL"));
						item2->setText(5, QString("UNKNOWN")); break;
					}
					case LANG_BULGARIAN: {
						item2->setText(4, QString("LANG_BULGARIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_BULGARIAN_BULGARIA                 :item2->setText(5, QString("SUBLANG_BULGARIAN_BULGARIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CATALAN: {
						item2->setText(4, QString("LANG_CATALAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CATALAN_CATALAN                    :item2->setText(5, QString("SUBLANG_CATALAN_CATALAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CENTRAL_KURDISH: {
						item2->setText(4, QString("LANG_CENTRAL_KURDISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CENTRAL_KURDISH_IRAQ               :item2->setText(5, QString("SUBLANG_CENTRAL_KURDISH_IRAQ")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CHEROKEE: {
						item2->setText(4, QString("LANG_CHEROKEE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CHEROKEE_CHEROKEE                  :item2->setText(5, QString("SUBLANG_CHEROKEE_CHEROKEE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CHINESE: {
						item2->setText(4, QString("LANG_CHINESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CHINESE_HONGKONG                   :item2->setText(5, QString("SUBLANG_CHINESE_HONGKONG")); break;
						case SUBLANG_CHINESE_MACAU                      :item2->setText(5, QString("SUBLANG_CHINESE_MACAU")); break;
						case SUBLANG_CHINESE_SINGAPORE                  :item2->setText(5, QString("SUBLANG_CHINESE_SINGAPORE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_CHINESE_TRADITIONAL: {
						item2->setText(4, QString("LANG_CHINESE_TRADITIONAL"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CHINESE_TRADITIONAL                :item2->setText(5, QString("SUBLANG_CHINESE_TRADITIONAL")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CORSICAN: {
						item2->setText(4, QString("LANG_CORSICAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CORSICAN_FRANCE                    :item2->setText(5, QString("SUBLANG_CORSICAN_FRANCE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_CZECH: {
						item2->setText(4, QString("LANG_CZECH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_CZECH_CZECH_REPUBLIC               :item2->setText(5, QString("SUBLANG_CZECH_CZECH_REPUBLIC")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_DANISH: {
						item2->setText(4, QString("LANG_DANISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_DANISH_DENMARK                     :item2->setText(5, QString("SUBLANG_DANISH_DENMARK")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_DARI: {
						item2->setText(4, QString("LANG_DARI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_DARI_AFGHANISTAN                   :item2->setText(5, QString("SUBLANG_DARI_AFGHANISTAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_DIVEHI: {
						item2->setText(4, QString("LANG_DIVEHI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_DIVEHI_MALDIVES                    :item2->setText(5, QString("SUBLANG_DIVEHI_MALDIVES")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_DUTCH: {
						item2->setText(4, QString("LANG_DUTCH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_DUTCH_BELGIAN                      :item2->setText(5, QString("SUBLANG_DUTCH_BELGIAN")); break;
						case SUBLANG_DUTCH                              :item2->setText(5, QString("SUBLANG_DUTCH")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ENGLISH: {
						item2->setText(4, QString("LANG_ENGLISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ENGLISH_AUS                        :item2->setText(5, QString("SUBLANG_ENGLISH_AUS")); break;
						case SUBLANG_ENGLISH_BELIZE                     :item2->setText(5, QString("SUBLANG_ENGLISH_BELIZE")); break;
						case SUBLANG_ENGLISH_CAN                        :item2->setText(5, QString("SUBLANG_ENGLISH_CAN")); break;
						case SUBLANG_ENGLISH_CARIBBEAN                  :item2->setText(5, QString("SUBLANG_ENGLISH_CARIBBEAN")); break;
						case SUBLANG_ENGLISH_INDIA                      :item2->setText(5, QString("SUBLANG_ENGLISH_INDIA")); break;
						case 	SUBLANG_ENGLISH_EIRE                    :item2->setText(5, QString("SUBLANG_ENGLISH_EIRE")); break;
						case SUBLANG_ENGLISH_JAMAICA                    :item2->setText(5, QString("SUBLANG_ENGLISH_JAMAICA")); break;
						case SUBLANG_ENGLISH_MALAYSIA                   :item2->setText(5, QString("SUBLANG_ENGLISH_MALAYSIA")); break;
						case SUBLANG_ENGLISH_NZ                         :item2->setText(5, QString("SUBLANG_ENGLISH_NZ")); break;
						case SUBLANG_ENGLISH_PHILIPPINES                :item2->setText(5, QString("SUBLANG_ENGLISH_PHILIPPINES")); break;
						case 	SUBLANG_ENGLISH_SINGAPORE               :item2->setText(5, QString("SUBLANG_ENGLISH_SINGAPORE")); break;
						case SUBLANG_ENGLISH_SOUTH_AFRICA               :item2->setText(5, QString("SUBLANG_ENGLISH_SOUTH_AFRICA")); break;
						case SUBLANG_ENGLISH_TRINIDAD                   :item2->setText(5, QString("SUBLANG_ENGLISH_TRINIDAD")); break;
						case SUBLANG_ENGLISH_UK                         :item2->setText(5, QString("SUBLANG_ENGLISH_UK")); break;
						case 	SUBLANG_ENGLISH_US                      :item2->setText(5, QString("SUBLANG_ENGLISH_US")); break;
						case SUBLANG_ENGLISH_ZIMBABWE                   :item2->setText(5, QString("SUBLANG_ENGLISH_ZIMBABWE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ESTONIAN: {
						item2->setText(4, QString("LANG_ESTONIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ESTONIAN_ESTONIA                   :item2->setText(5, QString("SUBLANG_ESTONIAN_ESTONIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_FAEROESE: {
						item2->setText(4, QString("LANG_FAEROESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_FAEROESE_FAROE_ISLANDS             :item2->setText(5, QString("SUBLANG_FAEROESE_FAROE_ISLANDS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					//case LANG_FARSI:  deprecated
					case LANG_FILIPINO: {
						item2->setText(4, QString("LANG_FILIPINO"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_FILIPINO_PHILIPPINES               :item2->setText(5, QString("SUBLANG_FILIPINO_PHILIPPINES")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_FINNISH: {
						item2->setText(4, QString("LANG_FINNISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_FINNISH_FINLAND                    :item2->setText(5, QString("SUBLANG_FINNISH_FINLAND")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_FRENCH: {
						item2->setText(4, QString("LANG_FRENCH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_FRENCH_BELGIAN                     :item2->setText(5, QString("SUBLANG_FRENCH_BELGIAN")); break;
						case SUBLANG_FRENCH_CANADIAN                    :item2->setText(5, QString("SUBLANG_FRENCH_CANADIAN")); break;
						case SUBLANG_FRENCH                             :item2->setText(5, QString("SUBLANG_FRENCH")); break;
						case SUBLANG_FRENCH_LUXEMBOURG                  :item2->setText(5, QString("SUBLANG_FRENCH_LUXEMBOURG")); break;
						case SUBLANG_FRENCH_MONACO                      :item2->setText(5, QString("SUBLANG_FRENCH_MONACO")); break;
						case SUBLANG_FRENCH_SWISS                       :item2->setText(5, QString("SUBLANG_FRENCH_SWISS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_FRISIAN: {
						item2->setText(4, QString("LANG_FRISIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_FRISIAN_NETHERLANDS                :item2->setText(5, QString("SUBLANG_FRISIAN_NETHERLANDS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					//case LANG_FULAH: deprecated
					case LANG_GALICIAN: {
						item2->setText(4, QString("LANG_GALICIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GALICIAN_GALICIAN                  :item2->setText(5, QString("SUBLANG_GALICIAN_GALICIAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_GEORGIAN: {
						item2->setText(4, QString("LANG_GEORGIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GEORGIAN_GEORGIA                   :item2->setText(5, QString("SUBLANG_GEORGIAN_GEORGIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_GERMAN: {
						item2->setText(4, QString("LANG_GERMAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GERMAN_AUSTRIAN                    :item2->setText(5, QString("SUBLANG_GERMAN_AUSTRIAN")); break;
						case SUBLANG_GERMAN                             :item2->setText(5, QString("SUBLANG_GERMAN")); break;
						case SUBLANG_GERMAN_LIECHTENSTEIN               :item2->setText(5, QString("SUBLANG_GERMAN_LIECHTENSTEIN")); break;
						case SUBLANG_GERMAN_LUXEMBOURG                  :item2->setText(5, QString("SUBLANG_GERMAN_LUXEMBOURG")); break;
						case SUBLANG_GERMAN_SWISS                       :item2->setText(5, QString("SUBLANG_GERMAN_SWISS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_GREEK: {
						item2->setText(4, QString("LANG_GREEK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GREEK_GREECE                       :item2->setText(5, QString("SUBLANG_GREEK_GREECE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_GREENLANDIC: {
						item2->setText(4, QString("LANG_GREENLANDIC"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GREENLANDIC_GREENLAND              :item2->setText(5, QString("SUBLANG_GREENLANDIC_GREENLAND")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_GUJARATI: {
						item2->setText(4, QString("LANG_GUJARATI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_GUJARATI_INDIA                     :item2->setText(5, QString("SUBLANG_GUJARATI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_HAUSA: {
						item2->setText(4, QString("LANG_HAUSA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_HAUSA_NIGERIA_LATIN                :item2->setText(5, QString("SUBLANG_HAUSA_NIGERIA_LATIN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_HAWAIIAN: {
						item2->setText(4, QString("LANG_HAWAIIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_HAWAIIAN_US                        :item2->setText(5, QString("SUBLANG_HAWAIIAN_US")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_HEBREW: {
						item2->setText(4, QString("LANG_HEBREW"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_HEBREW_ISRAEL                      :item2->setText(5, QString("SUBLANG_HEBREW_ISRAEL")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_HINDI: {
						item2->setText(4, QString("LANG_HINDI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_HINDI_INDIA                        :item2->setText(5, QString("SUBLANG_HINDI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_HUNGARIAN:{
						item2->setText(4, QString("LANG_HUNGARIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_HUNGARIAN_HUNGARY                  :item2->setText(5, QString("SUBLANG_HUNGARIAN_HUNGARY")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ICELANDIC: {
						item2->setText(4, QString("LANG_ICELANDIC"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ICELANDIC_ICELAND                  :item2->setText(5, QString("SUBLANG_ICELANDIC_ICELANDY")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_IGBO: {
						item2->setText(4, QString("LANG_IGBO"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_IGBO_NIGERIA                       :item2->setText(5, QString("SUBLANG_IGBO_NIGERIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_INDONESIAN: {
						item2->setText(4, QString("LANG_INDONESIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_INDONESIAN_INDONESIA               :item2->setText(5, QString("SUBLANG_INDONESIAN_INDONESIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_INUKTITUT: {
						item2->setText(4, QString("LANG_INUKTITUT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_INUKTITUT_CANADA_LATIN             :item2->setText(5, QString("SUBLANG_INUKTITUT_CANADA_LATIN")); break;
						case SUBLANG_INUKTITUT_CANADA                   :item2->setText(5, QString("SUBLANG_INUKTITUT_CANADA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_IRISH: {
						item2->setText(4, QString("LANG_IRISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_IRISH_IRELAND                      :item2->setText(5, QString("SUBLANG_IRISH_IRELAND")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ITALIAN: {
						item2->setText(4, QString("LANG_ITALIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ITALIAN                            :item2->setText(5, QString("SUBLANG_ITALIAN")); break;
						case SUBLANG_ITALIAN_SWISS                      :item2->setText(5, QString("SUBLANG_ITALIAN_SWISS")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_JAPANESE: {
						item2->setText(4, QString("LANG_JAPANESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_JAPANESE_JAPAN                     :item2->setText(5, QString("SUBLANG_JAPANESE_JAPAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KANNADA: {
						item2->setText(4, QString("LANG_KANNADA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KANNADA_INDIA                      :item2->setText(5, QString("SUBLANG_KANNADA_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KASHMIRI: {
						item2->setText(4, QString("LANG_KASHMIRI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KASHMIRI_INDIA                     :item2->setText(5, QString("SUBLANG_KASHMIRI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KAZAK: {
						item2->setText(4, QString("LANG_KAZAK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KAZAK_KAZAKHSTAN                   :item2->setText(5, QString("SUBLANG_KAZAK_KAZAKHSTAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KHMER: {
						item2->setText(4, QString("LANG_KHMER"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KHMER_CAMBODIA                     :item2->setText(5, QString("SUBLANG_KHMER_CAMBODIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KICHE: {
						item2->setText(4, QString("LANG_KICHE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KICHE_GUATEMALA                    :item2->setText(5, QString("SUBLANG_KICHE_GUATEMALA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KINYARWANDA: {
						item2->setText(4, QString("LANG_KINYARWANDA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KINYARWANDA_RWANDA                 :item2->setText(5, QString("SUBLANG_KINYARWANDA_RWANDA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KONKANI: {
						item2->setText(4, QString("LANG_KONKANI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KONKANI_INDIA                      :item2->setText(5, QString("SUBLANG_KONKANI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KOREAN: {
						item2->setText(4, QString("LANG_KOREAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KOREAN                             :item2->setText(5, QString("SUBLANG_KOREAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_KYRGYZ: {
						item2->setText(4, QString("LANG_KYRGYZ"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_KYRGYZ_KYRGYZSTAN                  :item2->setText(5, QString("SUBLANG_KYRGYZ_KYRGYZSTAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_LAO: {
						item2->setText(4, QString("LANG_LAO"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_LAO_LAO                            :item2->setText(5, QString("SUBLANG_LAO_LAO")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_LATVIAN: {
						item2->setText(4, QString("LANG_LATVIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_LATVIAN_LATVIA                     :item2->setText(5, QString("SUBLANG_LATVIAN_LATVIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_LITHUANIAN: {
						item2->setText(4, QString("LANG_LITHUANIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_LITHUANIAN                         :item2->setText(5, QString("SUBLANG_LITHUANIAN_LITHUANIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_LOWER_SORBIAN: {
						item2->setText(4, QString("LANG_LOWER_SORBIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_LOWER_SORBIAN_GERMANY              :item2->setText(5, QString("SUBLANG_LOWER_SORBIAN_GERMANY")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_LUXEMBOURGISH: {
						item2->setText(4, QString("LANG_LUXEMBOURGISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_LUXEMBOURGISH_LUXEMBOURG           :item2->setText(5, QString("SUBLANG_LUXEMBOURGISH_LUXEMBOURG")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MACEDONIAN: {
						item2->setText(4, QString("LANG_MACEDONIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MACEDONIAN_MACEDONIA               :item2->setText(5, QString("SUBLANG_MACEDONIAN_MACEDONIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MALAY: {
						item2->setText(4, QString("LANG_MALAY"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MALAY_BRUNEI_DARUSSALAM            :item2->setText(5, QString("SUBLANG_MALAY_BRUNEI_DARUSSALAM")); break;
						case SUBLANG_MALAY_MALAYSIA                     :item2->setText(5, QString("SUBLANG_MALAY_MALAYSIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MALAYALAM: {
						item2->setText(4, QString("LANG_MALAYALAM"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MALAYALAM_INDIA                    :item2->setText(5, QString("SUBLANG_MALAYALAM_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MALTESE: {
						item2->setText(4, QString("LANG_MALTESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MALTESE_MALTA                      :item2->setText(5, QString("SUBLANG_MALTESE_MALTA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					//case LANG_MANIPURI: reserved
					case LANG_MAORI: {
						item2->setText(4, QString("LANG_MAORI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MAORI_NEW_ZEALAND                  :item2->setText(5, QString("SUBLANG_MAORI_NEW_ZEALAND")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MAPUDUNGUN: {
						item2->setText(4, QString("LANG_MAPUDUNGUN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MAPUDUNGUN_CHILE                   :item2->setText(5, QString("SUBLANG_MAPUDUNGUN_CHILE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MARATHI: {
						item2->setText(4, QString("LANG_MARATHI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MARATHI_INDIA                      :item2->setText(5, QString("SUBLANG_MARATHI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MOHAWK: {
						item2->setText(4, QString("LANG_MOHAWK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MOHAWK_MOHAWK                      :item2->setText(5, QString("SUBLANG_MOHAWK_MOHAWK")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_MONGOLIAN: {
						item2->setText(4, QString("LANG_MONGOLIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA        :item2->setText(5, QString("SUBLANG_MONGOLIAN_CYRILLIC_MONGOLIA")); break;
						case SUBLANG_MONGOLIAN_PRC                      :item2->setText(5, QString("SUBLANG_MONGOLIAN_PRC")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_NEPALI: {
						item2->setText(4, QString("LANG_NEPALI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_NEPALI_NEPAL                       :item2->setText(5, QString("SUBLANG_NEPALI_NEPAL")); break;
						case SUBLANG_NEPALI_INDIA                       :item2->setText(5, QString("SUBLANG_NEPALI_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_NORWEGIAN: {
						item2->setText(4, QString("LANG_NORWEGIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_NORWEGIAN_BOKMAL                   :item2->setText(5, QString("SUBLANG_NORWEGIAN_BOKMAL")); break;
						case SUBLANG_NORWEGIAN_NYNORSK                  :item2->setText(5, QString("SUBLANG_NORWEGIAN_NYNORSK")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_OCCITAN: {
						item2->setText(4, QString("LANG_OCCITAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_OCCITAN_FRANCE                     :item2->setText(5, QString("SUBLANG_OCCITAN_FRANCE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ODIA: {
						item2->setText(4, QString("LANG_ODIA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ODIA_INDIA                         :item2->setText(5, QString("SUBLANG_ODIA_INDIA")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_PASHTO: {
						item2->setText(4, QString("LANG_PASHTO"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_PASHTO_AFGHANISTAN                 :item2->setText(5, QString("SUBLANG_PASHTO_AFGHANISTAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_POLISH: {
						item2->setText(4, QString("LANG_POLISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_POLISH_POLAND                      :item2->setText(5, QString("SUBLANG_POLISH_POLAND")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_PERSIAN: {
						item2->setText(4, QString("LANG_PERSIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_PERSIAN_IRAN                       :item2->setText(5, QString("SUBLANG_PERSIAN_IRAN")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_PORTUGUESE: {
						item2->setText(4, QString("LANG_PORTUGUESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_PORTUGUESE_BRAZILIAN               :item2->setText(5, QString("SUBLANG_PORTUGUESE_BRAZILIAN")); break;
						case SUBLANG_PORTUGUESE                         :item2->setText(5, QString("SUBLANG_PORTUGUESE")); break;
						default                                         :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_PUNJABI: {
						item2->setText(4, QString("LANG_PUNJABI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_PUNJABI_INDIA                     :item2->setText(5, QString("SUBLANG_PUNJABI_INDIA")); break;
						case SUBLANG_PUNJABI_PAKISTAN                  :item2->setText(5, QString("SUBLANG_PUNJABI_PAKISTAN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_QUECHUA: {
						item2->setText(4, QString("LANG_QUECHUA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_QUECHUA_BOLIVIA                   :item2->setText(5, QString("SUBLANG_QUECHUA_BOLIVIA")); break;
						case SUBLANG_QUECHUA_ECUADOR                   :item2->setText(5, QString("SUBLANG_QUECHUA_ECUADOR")); break;
						case SUBLANG_QUECHUA_PERU                      :item2->setText(5, QString("SUBLANG_QUECHUA_PERU")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ROMANIAN: {
						item2->setText(4, QString("LANG_ROMANIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ROMANIAN_ROMANIA                  :item2->setText(5, QString("SUBLANG_ROMANIAN_ROMANIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ROMANSH: {
						item2->setText(4, QString("LANG_ROMANSH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ROMANSH_SWITZERLAND               :item2->setText(5, QString("SUBLANG_ROMANSH_SWITZERLAND")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_PULAR: {
						item2->setText(4, QString("LANG_PULAR"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_PULAR_SENEGAL                     :item2->setText(5, QString("SUBLANG_PULAR_SENEGAL")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_RUSSIAN: {
						item2->setText(4, QString("LANG_RUSSIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_RUSSIAN_RUSSIA                    :item2->setText(5, QString("SUBLANG_RUSSIAN_RUSSIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SAKHA: {
						item2->setText(4, QString("LANG_SAKHA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SAKHA_RUSSIA                      :item2->setText(5, QString("SUBLANG_SAKHA_RUSSIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SAMI: {
						item2->setText(4, QString("LANG_SAMI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SAMI_INARI_FINLAND                :item2->setText(5, QString("SUBLANG_SAMI_INARI_FINLAND")); break;
						case SUBLANG_SAMI_LULE_NORWAY                  :item2->setText(5, QString("SUBLANG_SAMI_LULE_NORWAY")); break;
						case SUBLANG_SAMI_LULE_SWEDEN                  :item2->setText(5, QString("SUBLANG_SAMI_LULE_SWEDEN")); break;
						case SUBLANG_SAMI_NORTHERN_FINLAND             :item2->setText(5, QString("SUBLANG_SAMI_NORTHERN_FINLAND")); break;
						case SUBLANG_SAMI_NORTHERN_NORWAY              :item2->setText(5, QString("SUBLANG_SAMI_NORTHERN_NORWAY")); break;
						case SUBLANG_SAMI_NORTHERN_SWEDEN              :item2->setText(5, QString("SUBLANG_SAMI_NORTHERN_SWEDEN")); break;
						case SUBLANG_SAMI_SKOLT_FINLAND                :item2->setText(5, QString("SUBLANG_SAMI_SKOLT_FINLAND")); break;
						case SUBLANG_SAMI_SOUTHERN_NORWAY              :item2->setText(5, QString("SUBLANG_SAMI_SOUTHERN_NORWAY")); break;
						case SUBLANG_SAMI_SOUTHERN_SWEDEN              :item2->setText(5, QString("SUBLANG_SAMI_SOUTHERN_SWEDEN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SANSKRIT: {
						item2->setText(4, QString("LANG_SANSKRIT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SANSKRIT_INDIA                    :item2->setText(5, QString("SUBLANG_SANSKRIT_INDIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					//case LANG_SCOTTISH_GAELIC: ???

					//case LANG_SERBIAN_NEUTRAL:
					case LANG_SINDHI: {
						item2->setText(4, QString("LANG_SINDHI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SINDHI_AFGHANISTAN                :item2->setText(5, QString("SUBLANG_SINDHI_AFGHANISTAN")); break;
						case SUBLANG_SINDHI_INDIA                      :item2->setText(5, QString("SUBLANG_SINDHI_INDIA")); break;
						//case SUBLANG_SINDHI_PAKISTAN                 :item2->setText(5, QString("SUBLANG_SINDHI_PAKISTAN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SINHALESE: {
						item2->setText(4, QString("LANG_SINHALESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SINHALESE_SRI_LANKA               :item2->setText(5, QString("SUBLANG_SINHALESE_SRI_LANKA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SLOVAK: {
						item2->setText(4, QString("LANG_SLOVAK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SLOVAK_SLOVAKIA                   :item2->setText(5, QString("SUBLANG_SLOVAK_SLOVAKIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SLOVENIAN: {
						item2->setText(4, QString("LANG_SLOVENIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SLOVENIAN_SLOVENIA                :item2->setText(5, QString("SUBLANG_SLOVENIAN_SLOVENIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SOTHO: {
						item2->setText(4, QString("LANG_SOTHO"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA       :item2->setText(5, QString("SUBLANG_SOTHO_NORTHERN_SOUTH_AFRICA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SPANISH: {
						item2->setText(4, QString("LANG_SPANISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SPANISH_ARGENTINA                 :item2->setText(5, QString("SUBLANG_SPANISH_ARGENTINA")); break;
						case SUBLANG_SPANISH_BOLIVIA                   :item2->setText(5, QString("SUBLANG_SPANISH_BOLIVIA")); break;
						case SUBLANG_SPANISH_CHILE                     :item2->setText(5, QString("SUBLANG_SPANISH_CHILE")); break;
						case SUBLANG_SPANISH_COLOMBIA                  :item2->setText(5, QString("SUBLANG_SPANISH_COLOMBIA")); break;
						case SUBLANG_SPANISH_COSTA_RICA                :item2->setText(5, QString("SUBLANG_SPANISH_COSTA_RICA")); break;
						case SUBLANG_SPANISH_DOMINICAN_REPUBLIC        :item2->setText(5, QString("SUBLANG_SPANISH_DOMINICAN_REPUBLIC")); break;
						case SUBLANG_SPANISH_ECUADOR                   :item2->setText(5, QString("SUBLANG_SPANISH_ECUADOR")); break;
						case 	SUBLANG_SPANISH_EL_SALVADOR            :item2->setText(5, QString("SUBLANG_SPANISH_EL_SALVADOR")); break;
						case SUBLANG_SPANISH_GUATEMALA                 :item2->setText(5, QString("SUBLANG_SPANISH_GUATEMALA")); break;
						case SUBLANG_SPANISH_HONDURAS                  :item2->setText(5, QString("SUBLANG_SPANISH_HONDURAS")); break;
						case SUBLANG_SPANISH_MEXICAN                   :item2->setText(5, QString("SUBLANG_SPANISH_MEXICAN")); break;
						case SUBLANG_SPANISH_NICARAGUA                 :item2->setText(5, QString("SUBLANG_SPANISH_NICARAGUA")); break;
						case SUBLANG_SPANISH_PANAMA                    :item2->setText(5, QString("SUBLANG_SPANISH_PANAMA")); break;
						case SUBLANG_SPANISH_PARAGUAY                  :item2->setText(5, QString("SUBLANG_SPANISH_PARAGUAY")); break;
						case SUBLANG_SPANISH_PERU                      :item2->setText(5, QString("SUBLANG_SPANISH_PERU")); break;
						case SUBLANG_SPANISH_PUERTO_RICO               :item2->setText(5, QString("SUBLANG_SPANISH_PUERTO_RICO")); break;
						case SUBLANG_SPANISH_MODERN                    :item2->setText(5, QString("SUBLANG_SPANISH_MODERN")); break;
						case SUBLANG_SPANISH                           :item2->setText(5, QString("SUBLANG_SPANISH")); break;
						case SUBLANG_SPANISH_US                        :item2->setText(5, QString("SUBLANG_SPANISH_US")); break;
						case SUBLANG_SPANISH_URUGUAY                   :item2->setText(5, QString("SUBLANG_SPANISH_URUGUAY")); break;
						case SUBLANG_SPANISH_VENEZUELA                 :item2->setText(5, QString("SUBLANG_SPANISH_VENEZUELA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SWAHILI: {
						item2->setText(4, QString("LANG_SWAHILI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SWAHILI_KENYA                     :item2->setText(5, QString("SUBLANG_SWAHILI_KENYA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SWEDISH: {
						item2->setText(4, QString("LANG_SWEDISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SWEDISH_FINLAND                   :item2->setText(5, QString("SUBLANG_SWEDISH_FINLAND")); break;
						case SUBLANG_SWEDISH                           :item2->setText(5, QString("SUBLANG_SWEDISH")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_SYRIAC: {
						item2->setText(4, QString("LANG_SYRIAC"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_SYRIAC_SYRIA                      :item2->setText(5, QString("SUBLANG_SYRIAC_SYRIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TAJIK: {
						item2->setText(4, QString("LANG_TAJIK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TAJIK_TAJIKISTAN                  :item2->setText(5, QString("SUBLANG_TAJIK_TAJIKISTAN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TAMAZIGHT: {
						item2->setText(4, QString("LANG_TAMAZIGHT"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TAMAZIGHT_ALGERIA_LATIN           :item2->setText(5, QString("SUBLANG_TAMAZIGHT_ALGERIA_LATIN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TAMIL: {
						item2->setText(4, QString("LANG_TAMIL"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TAMIL_INDIA                       :item2->setText(5, QString("SUBLANG_TAMIL_INDIA")); break;
						case SUBLANG_TAMIL_SRI_LANKA                   :item2->setText(5, QString("SUBLANG_TAMIL_SRI_LANKA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TATAR: {
						item2->setText(4, QString("LANG_TATAR"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TATAR_RUSSIA                      :item2->setText(5, QString("SUBLANG_TATAR_RUSSIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TELUGU: {
						item2->setText(4, QString("LANG_TELUGU"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TELUGU_INDIA                      :item2->setText(5, QString("SUBLANG_TELUGU_INDIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_THAI: {
						item2->setText(4, QString("LANG_THAI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case 	SUBLANG_THAI_THAILAND                  :item2->setText(5, QString("SUBLANG_THAI_THAILAND")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TIBETAN: {
						item2->setText(4, QString("LANG_TIBETAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TIBETAN_PRC                       :item2->setText(5, QString("SUBLANG_TIBETAN_PRC")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TIGRIGNA: {
						item2->setText(4, QString("LANG_TIGRIGNA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case 	SUBLANG_TIGRINYA_ERITREA               :item2->setText(5, QString("SUBLANG_TIGRINYA_ERITREA")); break;
						case SUBLANG_TIGRINYA_ETHIOPIA                 :item2->setText(5, QString("SUBLANG_TIGRINYA_ETHIOPIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_TSWANA: {
						item2->setText(4, QString("LANG_TSWANA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TSWANA_BOTSWANA                   :item2->setText(5, QString("SUBLANG_TSWANA_BOTSWANA")); break;
						case 	SUBLANG_TSWANA_SOUTH_AFRICA            :item2->setText(5, QString("SUBLANG_TSWANA_SOUTH_AFRICA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TURKISH: {
						item2->setText(4, QString("LANG_TURKISH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TURKISH_TURKEY                    :item2->setText(5, QString("SUBLANG_TURKISH_TURKEY")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_TURKMEN: {
						item2->setText(4, QString("LANG_TURKMEN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_TURKMEN_TURKMENISTAN              :item2->setText(5, QString("SUBLANG_TURKMEN_TURKMENISTAN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_UIGHUR: {
						item2->setText(4, QString("LANG_UIGHUR"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_UIGHUR_PRC                        :item2->setText(5, QString("SUBLANG_UIGHUR_PRC")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_UKRAINIAN: {
						item2->setText(4, QString("LANG_UKRAINIAN"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_UKRAINIAN_UKRAINE                 :item2->setText(5, QString("SUBLANG_UKRAINIAN_UKRAINE")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_URDU: {
						item2->setText(4, QString("LANG_URDU"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_URDU_INDIA                        :item2->setText(5, QString("SUBLANG_URDU_INDIA")); break;
						case SUBLANG_URDU_PAKISTAN                     :item2->setText(5, QString("SUBLANG_URDU_PAKISTAN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_UZBEK: {
						item2->setText(4, QString("LANG_UZBEK"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_UZBEK_CYRILLIC                    :item2->setText(5, QString("SUBLANG_UZBEK_CYRILLIC")); break;
						case SUBLANG_UZBEK_LATIN                       :item2->setText(5, QString("SUBLANG_UZBEK_LATIN")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_VIETNAMESE: {
						item2->setText(4, QString("LANG_VIETNAMESE"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_VIETNAMESE_VIETNAM                :item2->setText(5, QString("SUBLANG_VIETNAMESE_VIETNAM")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_WELSH: {
						item2->setText(4, QString("LANG_WELSH"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_WELSH_UNITED_KINGDOM              :item2->setText(5, QString("SUBLANG_WELSH_UNITED_KINGDOM")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_WOLOF: {
						item2->setText(4, QString("LANG_WOLOF"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_WOLOF_SENEGAL                     :item2->setText(5, QString("SUBLANG_WOLOF_SENEGAL")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_XHOSA: {
						item2->setText(4, QString("LANG_XHOSA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_XHOSA_SOUTH_AFRICA                :item2->setText(5, QString("SUBLANG_XHOSA_SOUTH_AFRICA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}

					case LANG_YI: {
						item2->setText(4, QString("LANG_YI"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_YI_PRC                            :item2->setText(5, QString("SUBLANG_YI_PRC")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_YORUBA: {
						item2->setText(4, QString("LANG_YORUBA"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_YORUBA_NIGERIA                    :item2->setText(5, QString("SUBLANG_YORUBA_NIGERIA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					case LANG_ZULU: {
						item2->setText(4, QString("LANG_ZULU"));
						switch (SUBLANGID(file.resources[i].names[j].wIDLanguage)) {
						case SUBLANG_ZULU_SOUTH_AFRICA                 :item2->setText(5, QString("SUBLANG_ZULU_SOUTH_AFRICA")); break;
						default                                        :item2->setText(5, QString("UNKNOWN")); break;
						}
						break;
					}
					}
				}
				}
			}
		}
	}
}

void QtGuiPE_Resource::clear_fields() {
	ui.treeWidget->clear();
}