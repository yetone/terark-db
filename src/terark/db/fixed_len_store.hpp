#pragma once

#include <terark/db/db_index.hpp>
#include <terark/int_vector.hpp>
#include <terark/rank_select.hpp>
#include <terark/util/sortable_strvec.hpp>

namespace terark { namespace db {

class TERARK_DB_DLL FixedLenStore : public ReadableStore {
public:
	FixedLenStore();
	~FixedLenStore();

	llong dataStorageSize() const override;
	llong dataInflateSize() const override;
	llong numDataRows() const override;
	void getValueAppend(llong id, valvec<byte>* val, DbContext*) const override;
	StoreIterator* createStoreIterForward(DbContext*) const override;
	StoreIterator* createStoreIterBackward(DbContext*) const override;

	void build(const Schema& schema, SortableStrVec& strVec);
	void load(PathRef path) override;
	void save(PathRef path) const override;

protected:
	valvec<byte> m_keys;
	byte_t*      m_mmapBase;
	size_t       m_mmapSize;
	size_t       m_fixedLen;
	size_t       m_rows;

	std::pair<size_t, bool> searchLowerBound(fstring binkey) const;
};

}} // namespace terark::db