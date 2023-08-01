#include "AccountInfoData.h"
#include "MegaApplication.h"

using namespace mega;

AccountInfoData::AccountInfoData(QObject *parent)
    : QObject(parent)
    , mMegaApi(MegaSyncApp->getMegaApi())
    , mDelegateListener(new QTMegaRequestListener(mMegaApi, this))
    , mType(AccountType::ACCOUNT_TYPE_FREE)
    , mTotalStorage(QString())
{
    requestAccountInfoData();
}

void AccountInfoData::requestAccountInfoData()
{
    mMegaApi->getAccountDetails(this->mDelegateListener.get());
}

void AccountInfoData::aboutToBeDestroyed()
{
    mDelegateListener = nullptr;
}

void AccountInfoData::onRequestFinish(MegaApi*, MegaRequest* request, MegaError* error)
{
    switch(request->getType())
    {
        case MegaRequest::TYPE_ACCOUNT_DETAILS:
        {
            if(error->getErrorCode() == MegaError::API_OK)
            {
                qDebug() << "AccountInfoData::onRequestFinish -> TYPE_ACCOUNT_DETAILS API_OK";
                std::unique_ptr<mega::QTMegaRequestListener> mDelegateListener;
                MegaAccountDetails* accountDetails = request->getMegaAccountDetails();
                mType = static_cast<AccountInfoData::AccountType>(accountDetails->getProLevel());
                mTotalStorage = Utilities::getSizeString(accountDetails->getStorageMax());
                emit accountDetailsChanged();
            } else {
                qDebug() << "AccountInfoData::onRequestFinish -> TYPE_ACCOUNT_DETAILS Error code -> " << error->getErrorCode();
            }
        }
    }
}
