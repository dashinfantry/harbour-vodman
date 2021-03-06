/* The MIT License (MIT)
 *
 * Copyright (c) 2018 Jean Gressmann <jean@0x42.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "VMVod.h"

#include <QDebug>
#include <QDebugStateSaver>
#include <QDataStream>


VMVodEnums::~VMVodEnums()
{

}

VMVodEnums::VMVodEnums(QObject* parent)
    : QObject(parent)
{}


/////////////////////////////////////////////////////////////////////////////

VMVodFormat::VMVodFormat()
    : d(new VMVodFormatData())
{

}

bool VMVodFormat::isValid() const
{
    return !d->_id.isEmpty() &&
           !d->_vodUrl.isEmpty();
}

////////////////////////////////////////////////////////////////////

VMVodDescription::VMVodDescription()
    : d(new VMVodDescriptionData())
{

}

bool VMVodDescription::isValid() const
{
    return !d->_id.isEmpty();
}

////////////////////////////////////////////////////////////////////


VMVod::VMVod()
    : d(new VMVodData())
{
}

bool VMVod::isValid() const
{
    return d->_formats.size() > 0 && d->description.isValid();
}

QVariant VMVod::format(int index) const {
    return QVariant::fromValue(d->_formats[index]);
}

////////////////////////////////////////////////////////////////////////////////

QDataStream &operator<<(QDataStream &stream, const VMVodFormatData &value)
{
                       stream << value._width;
                       stream << value._height;
                       stream << value._id;
                       stream << value._displayName;
                       stream << value._fileExtension;
                       stream << value._vodUrl;
                       stream << value._fileSize;
                       stream << value._format;
                       stream << value._frameRate;
                       stream << value._fileUrl;
                       return stream;
                       }

QDataStream &operator>>(QDataStream &stream, VMVodFormatData &value) {
                       stream >> value._width;
                       stream >> value._height;
                       stream >> value._id;
                       stream >> value._displayName;
                       stream >> value._fileExtension;
                       stream >> value._vodUrl;
                       stream >> value._fileSize;
                       stream >> value._format;
                       stream >> value._frameRate;
                       stream >> value._fileUrl;
                       return stream;
                       }

QDataStream &operator<<(QDataStream &stream, const VMVodFormat &value) {
                       return stream << value.data();
                       }

QDataStream &operator>>(QDataStream &stream, VMVodFormat &value) {
                       return stream >> value.data();
                       }

QDataStream &operator<<(QDataStream &stream, const VMVodDescriptionData &value) {
    stream << value._thumbnail;
    stream << value._webPageUrl;
    stream << value._title;
    stream << value._fullTitle;
    stream << value.durationS;
    stream << value._id;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, VMVodDescriptionData &value) {
    stream >> value._thumbnail;
    stream >> value._webPageUrl;
    stream >> value._title;
    stream >> value._fullTitle;
    stream >> value.durationS;
    stream >> value._id;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const VMVodDescription &value) {
    return stream << value.data();
}

QDataStream &operator>>(QDataStream &stream, VMVodDescription &value) {
    return stream >> value.data();
}

QDataStream &operator<<(QDataStream &stream, const VMVodData &value) {
    stream << value.description;
    stream << value._formats;
    return stream;
}

QDataStream &operator>>(QDataStream &stream, VMVodData &value) {
    stream >> value.description;
    stream >> value._formats;
    return stream;
}

QDataStream &operator<<(QDataStream &stream, const VMVod &value) {
    return stream << value.data();
}

QDataStream &operator>>(QDataStream &stream, VMVod &value) {
    return stream >> value.data();
}


QDebug operator<<(QDebug debug, const VMVod& value) {
    const VMVodData& data = value.data();
    QDebugStateSaver saver(debug);
    debug.nospace() << "VMVod("
                    << "desc=" << data.description
                    << ", #formats=" << data._formats.size()
                    << ")";
    return debug;
}

QDebug operator<<(QDebug debug, const VMVodDescription& value) {
    const VMVodDescriptionData& data = value.data();
    QDebugStateSaver saver(debug);
    debug.nospace() << "VMVodDescription("
                    << "id=" << data._id
                    << ", title=" << data._title
                    << ", fullTitle=" << data._fullTitle
                    << ", thumbnail=" << data._thumbnail
                    << ", webpageUrl=" << data._webPageUrl
                    << ", durationS=" << data.durationS
                    << ")";
    return debug;
}

QDebug operator<<(QDebug debug, const VMVodFormat& value) {
    QDebugStateSaver saver(debug);
    debug.nospace() << "VMVodFormat("
                    << "name=" << value.displayName()
                    << ", id=" << value.id()
                    << ", format=" << value.format()
                    << ", width=" << value.width()
                    << ", height=" << value.height()
                    << ", fps=" << value.frameRate()
                    << ", fileUrl=" << value.fileUrl()
                    << ", vodUrl=" << value.vodUrl()
                    << ", size=" << value.fileSize()
                    << ", ext=" << value.fileExtension()
                    << ")";
    return debug;
}

